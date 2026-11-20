(() => {
  const DEFAULT_SETTINGS = {
    enabled: true,
    handle: "ewerton",
    repo: "ewertonManoel/Codeforces",
    branch: "main",
    folder: "solutions",
    token: "",
    addHeader: true
  };

  const NORMAL_POLL_MS = 8000;
  const FAST_POLL_MS = 3000;
  const FAST_POLL_WINDOW_MS = 3 * 60 * 1000;

  let pollTimer = null;
  let fastPollUntil = 0;
  let isChecking = false;
  const inFlightIds = new Set();

  function showToast(text, kind = "success", linkUrl = null) {
    let container = document.getElementById("cf-gh-toast-container");
    if (!container) {
      container = document.createElement("div");
      container.id = "cf-gh-toast-container";
      Object.assign(container.style, {
        position: "fixed",
        bottom: "20px",
        right: "20px",
        zIndex: "999999",
        display: "flex",
        flexDirection: "column",
        gap: "8px",
        fontFamily: "-apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif"
      });
      document.body.appendChild(container);
    }

    const toast = document.createElement("div");
    const colors = {
      success: { bg: "#0f172a", border: "#22c55e", text: "#f8fafc" },
      info: { bg: "#0f172a", border: "#38bdf8", text: "#f8fafc" },
      error: { bg: "#1f1215", border: "#ef4444", text: "#fecaca" }
    };
    const palette = colors[kind] || colors.info;

    Object.assign(toast.style, {
      background: palette.bg,
      color: palette.text,
      border: `1px solid ${palette.border}`,
      borderLeft: `4px solid ${palette.border}`,
      borderRadius: "8px",
      padding: "10px 14px",
      fontSize: "13px",
      lineHeight: "1.4",
      boxShadow: "0 10px 25px rgba(0, 0, 0, 0.35)",
      maxWidth: "340px",
      display: "flex",
      alignItems: "center",
      gap: "10px"
    });

    const msgSpan = document.createElement("span");
    msgSpan.textContent = text;
    toast.appendChild(msgSpan);

    if (linkUrl) {
      const a = document.createElement("a");
      a.href = linkUrl;
      a.target = "_blank";
      a.rel = "noopener noreferrer";
      a.textContent = "Ver";
      Object.assign(a.style, {
        color: "#38bdf8",
        fontWeight: "600",
        textDecoration: "underline",
        marginLeft: "auto",
        whiteSpace: "nowrap"
      });
      toast.appendChild(a);
    }

    container.appendChild(toast);
    setTimeout(() => {
      toast.style.transition = "opacity 0.25s ease";
      toast.style.opacity = "0";
      setTimeout(() => toast.remove(), 300);
    }, 5500);
  }

  async function getState() {
    const data = await chrome.storage.local.get([
      "settings",
      "baselineSubmissionId",
      "syncedSubmissionIds"
    ]);
    return {
      settings: { ...DEFAULT_SETTINGS, ...(data.settings || {}) },
      baselineSubmissionId: typeof data.baselineSubmissionId === "number" ? data.baselineSubmissionId : null,
      syncedSubmissionIds: Array.isArray(data.syncedSubmissionIds) ? data.syncedSubmissionIds : []
    };
  }

  function buildSubmissionUrl(sub) {
    const contestId = sub.contestId || sub.problem?.contestId;
    if (!contestId) return null;
    if (contestId >= 100000) {
      return `https://codeforces.com/gym/${contestId}/submission/${sub.id}`;
    }
    return `https://codeforces.com/contest/${contestId}/submission/${sub.id}`;
  }

  function buildProblemUrl(sub) {
    const contestId = sub.contestId || sub.problem?.contestId;
    const index = sub.problem?.index;
    if (!contestId || !index) return null;
    if (contestId >= 100000) {
      return `https://codeforces.com/gym/${contestId}/problem/${index}`;
    }
    return `https://codeforces.com/contest/${contestId}/problem/${index}`;
  }

  function getCsrfTokenFromDom() {
    const meta = document.querySelector('meta[name="X-Csrf-Token"]');
    if (meta && meta.content) return meta.content;
    const input = document.querySelector('input[name="csrf_token"]');
    if (input && input.value) return input.value;
    return null;
  }

  async function fetchSourceCode(sub) {
    const submissionUrl = buildSubmissionUrl(sub);

    // Method 1: Fetch authenticated submission page directly on codeforces.com
    if (submissionUrl) {
      try {
        const resp = await fetch(submissionUrl, { credentials: "include" });
        if (resp.ok) {
          const html = await resp.text();
          const doc = new DOMParser().parseFromString(html, "text/html");
          const pre = doc.querySelector("#program-source-text");
          if (pre && pre.textContent && pre.textContent.trim().length > 0) {
            return { code: pre.textContent, submissionUrl };
          }
        }
      } catch {
        // Fall through to Method 2
      }
    }

    // Method 2: Codeforces internal AJAX endpoint /data/submitSource
    const csrf = getCsrfTokenFromDom();
    if (csrf) {
      const formBody = new URLSearchParams({
        submissionId: String(sub.id),
        csrf_token: csrf
      });
      const resp = await fetch("https://codeforces.com/data/submitSource", {
        method: "POST",
        credentials: "include",
        headers: {
          "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
          "X-Requested-With": "XMLHttpRequest"
        },
        body: formBody.toString()
      });
      if (resp.ok) {
        const json = await resp.json();
        if (json && typeof json.source === "string" && json.source.trim().length > 0) {
          return { code: json.source, submissionUrl };
        }
      }
    }

    throw new Error(`Could not fetch source code for submission #${sub.id}. Make sure you are signed in to Codeforces.`);
  }

  async function syncSubmission(sub, { silent = false } = {}) {
    if (inFlightIds.has(sub.id)) return { ok: false, error: "Already syncing" };
    inFlightIds.add(sub.id);

    try {
      const { code, submissionUrl } = await fetchSourceCode(sub);
      const payload = {
        submissionId: sub.id,
        contestId: sub.contestId || sub.problem?.contestId || "",
        index: sub.problem?.index || "",
        problemName: sub.problem?.name || `Problem_${sub.id}`,
        rating: sub.problem?.rating || null,
        tags: sub.problem?.tags || [],
        language: sub.programmingLanguage || "",
        timeMs: sub.timeConsumedMillis,
        memoryKb: typeof sub.memoryConsumedBytes === "number" ? Math.round(sub.memoryConsumedBytes / 1024) : null,
        problemUrl: buildProblemUrl(sub),
        submissionUrl,
        code
      };

      const response = await chrome.runtime.sendMessage({
        type: "PUSH_SUBMISSION",
        payload
      });

      if (!response || !response.ok) {
        throw new Error(response?.error || "Failed to push to GitHub");
      }

      if (!silent) {
        const label = `${payload.contestId}${payload.index} - ${payload.problemName}`;
        if (response.unchanged) {
          showToast(`Já atualizado no GitHub: ${label}`, "info", response.htmlUrl);
        } else {
          showToast(`Sincronizado no GitHub: ${label}`, "success", response.htmlUrl);
        }
      }
      return response;
    } catch (err) {
      if (!silent) {
        showToast(`Erro ao sincronizar #${sub.id}: ${err.message}`, "error");
      }
      return { ok: false, error: err.message };
    } finally {
      inFlightIds.delete(sub.id);
    }
  }

  async function fetchRecentSubmissions(handle, count = 10) {
    const res = await chrome.runtime.sendMessage({
      type: "FETCH_CF_STATUS",
      handle,
      count
    });
    if (!res || !res.ok) {
      throw new Error(res?.error || "Failed to query Codeforces API");
    }
    return res.submissions || [];
  }

  async function checkForNewAccepted() {
    if (isChecking || document.hidden) return;
    isChecking = true;

    try {
      const { settings, baselineSubmissionId, syncedSubmissionIds } = await getState();
      if (!settings.enabled || !settings.handle || !settings.token) return;

      const submissions = await fetchRecentSubmissions(settings.handle, 10);
      if (!submissions.length) {
        if (baselineSubmissionId === null) {
          await chrome.storage.local.set({ baselineSubmissionId: 0 });
        }
        return;
      }

      const newestId = submissions[0].id;

      // First run: set baseline so historical submissions aren't bulk-pushed
      if (baselineSubmissionId === null) {
        await chrome.storage.local.set({ baselineSubmissionId: newestId });
        return;
      }

      // If any submission is currently being judged, keep fast polling active
      const hasPending = submissions.some(
        (s) => s.id > baselineSubmissionId && (!s.verdict || s.verdict === "TESTING")
      );
      if (hasPending) {
        fastPollUntil = Math.max(fastPollUntil, Date.now() + 60000);
      }

      // Find all new Accepted submissions above baseline not yet synced (oldest first)
      const newAccepted = submissions
        .filter(
          (s) =>
            s.id > baselineSubmissionId &&
            s.verdict === "OK" &&
            !syncedSubmissionIds.includes(s.id) &&
            !inFlightIds.has(s.id)
        )
        .reverse();

      for (const sub of newAccepted) {
        await syncSubmission(sub);
      }

      // Advance baseline past completed verdicts only (don't skip still-testing ones)
      const lowestPendingId = submissions
        .filter((s) => s.id > baselineSubmissionId && (!s.verdict || s.verdict === "TESTING"))
        .reduce((min, s) => Math.min(min, s.id), Infinity);

      const safeBaseline = lowestPendingId === Infinity ? newestId : Math.max(baselineSubmissionId, lowestPendingId - 1);
      if (safeBaseline > baselineSubmissionId) {
        await chrome.storage.local.set({ baselineSubmissionId: safeBaseline });
      }
    } catch {
      // Quietly retry on next poll
    } finally {
      isChecking = false;
      scheduleNextPoll();
    }
  }

  function scheduleNextPoll() {
    if (pollTimer) clearTimeout(pollTimer);
    const delay = Date.now() < fastPollUntil ? FAST_POLL_MS : NORMAL_POLL_MS;
    pollTimer = setTimeout(checkForNewAccepted, delay);
  }

  function triggerFastPoll() {
    fastPollUntil = Date.now() + FAST_POLL_WINDOW_MS;
    if (pollTimer) clearTimeout(pollTimer);
    pollTimer = setTimeout(checkForNewAccepted, 2500);
  }

  // Detect form submissions (submit page or problem sidebar) to enter fast-poll mode
  function watchSubmitForms() {
    document.addEventListener(
      "submit",
      (ev) => {
        const form = ev.target;
        if (form && form.querySelector && form.querySelector('input[name="submittedProblemCode"], select[name="submittedProblemIndex"], textarea[name="source"], input[name="sourceFile"]')) {
          triggerFastPoll();
        }
      },
      true
    );

    if (/\/(my|status|submissions)\b/i.test(window.location.pathname)) {
      triggerFastPoll();
    }
  }

  // Inject a one-click "Sync to GitHub" button on individual submission pages
  function injectManualButtonOnSubmissionPage() {
    const match = window.location.pathname.match(/^\/(contest|gym)\/(\d+)\/submission\/(\d+)/);
    if (!match) return;
    const sourcePre = document.querySelector("#program-source-text");
    if (!sourcePre || document.getElementById("cf-gh-manual-btn")) return;

    const btn = document.createElement("button");
    btn.id = "cf-gh-manual-btn";
    btn.type = "button";
    btn.textContent = "⬆ Push to GitHub";
    Object.assign(btn.style, {
      marginLeft: "10px",
      padding: "4px 10px",
      fontSize: "12px",
      fontWeight: "600",
      borderRadius: "6px",
      border: "1px solid #38bdf8",
      background: "#0f172a",
      color: "#f8fafc",
      cursor: "pointer"
    });

    btn.addEventListener("click", async () => {
      btn.disabled = true;
      btn.textContent = "Syncing...";
      try {
        const { settings } = await getState();
        const subId = Number(match[3]);
        const contestId = Number(match[2]);
        const subs = await fetchRecentSubmissions(settings.handle, 50);
        let sub = subs.find((s) => s.id === subId);

        if (!sub) {
          // Fallback using DOM info from the submission page itself
          const problemLink = document.querySelector('a[href*="/problem/"]');
          const problemText = problemLink ? problemLink.textContent.trim() : `Submission_${subId}`;
          const idxMatch = problemLink?.getAttribute("href")?.match(/\/problem\/([^/]+)/);
          sub = {
            id: subId,
            contestId,
            programmingLanguage: "GNU C++",
            problem: {
              contestId,
              index: idxMatch ? idxMatch[1] : "",
              name: problemText.replace(/^[A-Z0-9]+\s*-\s*/i, "")
            }
          };
        }

        const res = await syncSubmission(sub);
        btn.textContent = res.ok ? "✓ Synced" : "Retry Push";
      } catch (err) {
        showToast(`Erro: ${err.message}`, "error");
        btn.textContent = "Retry Push";
      } finally {
        btn.disabled = false;
      }
    });

    const headerAnchor = sourcePre.parentElement?.querySelector(".copy-source, h4, .caption") || sourcePre;
    headerAnchor.parentElement?.insertBefore(btn, headerAnchor);
  }

  // Listen to manual sync requests from the popup ("Sync latest Accepted")
  chrome.runtime.onMessage.addListener((message, _sender, sendResponse) => {
    if (message?.type === "SYNC_LATEST_ACCEPTED") {
      (async () => {
        try {
          const { settings } = await getState();
          if (!settings.handle || !settings.token) {
            throw new Error("Configure your handle and GitHub token first.");
          }
          const submissions = await fetchRecentSubmissions(settings.handle, 30);
          const latestOk = submissions.find((s) => s.verdict === "OK");
          if (!latestOk) {
            throw new Error(`No recent Accepted submission found for ${settings.handle}.`);
          }
          const result = await syncSubmission(latestOk);
          sendResponse(result);
        } catch (err) {
          sendResponse({ ok: false, error: err.message });
        }
      })();
      return true;
    }
  });

  document.addEventListener("visibilitychange", () => {
    if (!document.hidden) {
      checkForNewAccepted();
    }
  });

  watchSubmitForms();
  injectManualButtonOnSubmissionPage();
  checkForNewAccepted();
})();
