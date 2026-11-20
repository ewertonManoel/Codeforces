const DEFAULT_SETTINGS = {
  enabled: true,
  handle: "ewerton",
  repo: "ewertonManoel/Codeforces",
  branch: "main",
  folder: "solutions",
  token: "",
  addHeader: true
};

function encodeBase64Utf8(text) {
  const bytes = new TextEncoder().encode(text);
  let binary = "";
  const chunkSize = 0x8000;
  for (let i = 0; i < bytes.length; i += chunkSize) {
    binary += String.fromCharCode(...bytes.subarray(i, i + chunkSize));
  }
  return btoa(binary);
}

function decodeBase64Utf8(base64) {
  const clean = base64.replace(/\s+/g, "");
  const binary = atob(clean);
  const bytes = new Uint8Array(binary.length);
  for (let i = 0; i < binary.length; i++) {
    bytes[i] = binary.charCodeAt(i);
  }
  return new TextDecoder().decode(bytes);
}

function getFileExtension(language = "") {
  const lang = language.toLowerCase();
  if (lang.includes("c++") || lang.includes("g++") || lang.includes("clang++")) return "cpp";
  if (lang.includes("c#") || lang.includes("csharp")) return "cs";
  if (lang.includes("gnu c") || lang.includes("gcc") || lang === "c") return "c";
  if (lang.includes("python") || lang.includes("pypy")) return "py";
  if (lang.includes("javascript") || lang.includes("node")) return "js";
  if (lang.includes("typescript")) return "ts";
  if (lang.includes("java")) return "java";
  if (lang.includes("rust")) return "rs";
  if (lang.includes("go")) return "go";
  if (lang.includes("kotlin")) return "kt";
  if (lang.includes("ruby")) return "rb";
  if (lang.includes("haskell")) return "hs";
  if (lang.includes("pascal") || lang.includes("delphi")) return "pas";
  return "txt";
}

function getCommentPrefix(ext) {
  if (ext === "py" || ext === "rb") return "#";
  if (ext === "hs") return "--";
  return "//";
}

function sanitizeFileName(name) {
  return name
    .normalize("NFKD")
    .replace(/[\u0300-\u036f]/g, "")
    .replace(/[^a-zA-Z0-9]+/g, "_")
    .replace(/^_+|_+$/g, "")
    .slice(0, 80) || "solution";
}

function buildFileContent(payload, ext, addHeader) {
  const normalizedCode = (payload.code || "").replace(/\r\n/g, "\n").trimEnd() + "\n";
  if (!addHeader) return normalizedCode;

  const c = getCommentPrefix(ext);
  const problemCode = `${payload.contestId || ""}${payload.index || ""}`.trim();
  const lines = [
    `${c} Problem: ${problemCode ? `${problemCode} - ` : ""}${payload.problemName || "Unknown"}`,
  ];

  const metaParts = [];
  if (payload.contestId) metaParts.push(`Contest: ${payload.contestId}`);
  if (payload.rating) metaParts.push(`Rating: ${payload.rating}`);
  if (Array.isArray(payload.tags) && payload.tags.length > 0) {
    metaParts.push(`Tags: ${payload.tags.join(", ")}`);
  }
  if (metaParts.length > 0) lines.push(`${c} ${metaParts.join(" | ")}`);

  const perfParts = [];
  if (payload.language) perfParts.push(`Language: ${payload.language}`);
  if (payload.timeMs !== undefined && payload.timeMs !== null) perfParts.push(`Time: ${payload.timeMs} ms`);
  if (payload.memoryKb !== undefined && payload.memoryKb !== null) perfParts.push(`Memory: ${payload.memoryKb} KB`);
  if (perfParts.length > 0) lines.push(`${c} ${perfParts.join(" | ")}`);

  if (payload.problemUrl) lines.push(`${c} Problem Link: ${payload.problemUrl}`);
  if (payload.submissionUrl) lines.push(`${c} Submission: ${payload.submissionUrl}`);

  return `${lines.join("\n")}\n\n${normalizedCode}`;
}

async function getSettings() {
  const data = await chrome.storage.local.get(["settings"]);
  return { ...DEFAULT_SETTINGS, ...(data.settings || {}) };
}

async function recordSyncHistory(entry) {
  const data = await chrome.storage.local.get(["syncHistory", "syncedSubmissionIds"]);
  const history = Array.isArray(data.syncHistory) ? data.syncHistory : [];
  const syncedIds = Array.isArray(data.syncedSubmissionIds) ? data.syncedSubmissionIds : [];

  const updatedHistory = [entry, ...history.filter((h) => h.submissionId !== entry.submissionId)].slice(0, 20);
  const updatedIds = entry.submissionId && !syncedIds.includes(entry.submissionId)
    ? [entry.submissionId, ...syncedIds].slice(0, 500)
    : syncedIds;

  await chrome.storage.local.set({
    syncHistory: updatedHistory,
    syncedSubmissionIds: updatedIds
  });
}

async function pushToGitHub(payload) {
  const settings = await getSettings();
  if (!settings.token || !settings.repo || !settings.repo.includes("/")) {
    throw new Error("Configure your GitHub repository and Personal Access Token in the extension popup first.");
  }

  const [owner, repoName] = settings.repo.trim().split("/");
  const branch = (settings.branch || "main").trim();
  const folder = (settings.folder || "solutions").trim().replace(/^\/+|\/+$/g, "");
  const ext = getFileExtension(payload.language);
  const problemCode = `${payload.contestId || ""}${payload.index || ""}`.trim();
  const safeName = sanitizeFileName(payload.problemName || `submission_${payload.submissionId}`);
  const fileName = problemCode ? `${problemCode}_${safeName}.${ext}` : `${safeName}.${ext}`;
  const filePath = folder ? `${folder}/${fileName}` : fileName;

  const content = buildFileContent(payload, ext, settings.addHeader);
  const encodedPath = filePath.split("/").map(encodeURIComponent).join("/");
  const apiUrl = `https://api.github.com/repos/${encodeURIComponent(owner)}/${encodeURIComponent(repoName)}/contents/${encodedPath}`;

  const headers = {
    Authorization: `Bearer ${settings.token.trim()}`,
    Accept: "application/vnd.github+json",
    "Content-Type": "application/json",
    "X-GitHub-Api-Version": "2022-11-28"
  };

  let existingSha = null;
  const getResp = await fetch(`${apiUrl}?ref=${encodeURIComponent(branch)}`, { headers });
  if (getResp.ok) {
    const existing = await getResp.json();
    existingSha = existing.sha;
    if (existing.content) {
      const existingText = decodeBase64Utf8(existing.content);
      if (existingText === content) {
        await recordSyncHistory({
          submissionId: payload.submissionId,
          problemLabel: `${problemCode} - ${payload.problemName}`,
          filePath,
          htmlUrl: existing.html_url,
          status: "unchanged",
          timestamp: Date.now()
        });
        return { ok: true, unchanged: true, filePath, htmlUrl: existing.html_url };
      }
    }
  } else if (getResp.status !== 404) {
    const errBody = await getResp.json().catch(() => ({}));
    throw new Error(`GitHub GET failed (${getResp.status}): ${errBody.message || getResp.statusText}`);
  }

  const actionVerb = existingSha ? "Update" : "Add";
  const perfSummary = [payload.language, payload.timeMs != null ? `${payload.timeMs}ms` : null]
    .filter(Boolean)
    .join(", ");
  const commitMessage = `${actionVerb} ${problemCode ? `${problemCode} - ` : ""}${payload.problemName}${perfSummary ? ` (${perfSummary})` : ""}`;

  const body = {
    message: commitMessage,
    content: encodeBase64Utf8(content),
    branch
  };
  if (existingSha) body.sha = existingSha;

  const putResp = await fetch(apiUrl, {
    method: "PUT",
    headers,
    body: JSON.stringify(body)
  });

  if (!putResp.ok) {
    const errBody = await putResp.json().catch(() => ({}));
    throw new Error(`GitHub PUT failed (${putResp.status}): ${errBody.message || putResp.statusText}`);
  }

  const result = await putResp.json();
  const htmlUrl = result?.content?.html_url || `https://github.com/${owner}/${repoName}/blob/${branch}/${filePath}`;

  await recordSyncHistory({
    submissionId: payload.submissionId,
    problemLabel: `${problemCode ? `${problemCode} - ` : ""}${payload.problemName}`,
    filePath,
    htmlUrl,
    status: existingSha ? "updated" : "added",
    timestamp: Date.now()
  });

  try {
    chrome.notifications.create(`cf-sync-${payload.submissionId}`, {
      type: "basic",
      iconUrl: "icons/icon128.png",
      title: "Codeforces → GitHub",
      message: `${actionVerb === "Add" ? "Synced" : "Updated"} ${filePath}`
    });
  } catch {
    // Notifications are optional
  }

  return { ok: true, unchanged: false, updated: Boolean(existingSha), filePath, htmlUrl };
}

async function testGitHubConnection(settingsOverride) {
  const settings = { ...(await getSettings()), ...(settingsOverride || {}) };
  if (!settings.token || !settings.repo || !settings.repo.includes("/")) {
    throw new Error("Please provide both Repository (owner/repo) and GitHub Token.");
  }
  const [owner, repoName] = settings.repo.trim().split("/");
  const resp = await fetch(`https://api.github.com/repos/${encodeURIComponent(owner)}/${encodeURIComponent(repoName)}`, {
    headers: {
      Authorization: `Bearer ${settings.token.trim()}`,
      Accept: "application/vnd.github+json",
      "X-GitHub-Api-Version": "2022-11-28"
    }
  });

  if (!resp.ok) {
    const errBody = await resp.json().catch(() => ({}));
    throw new Error(`GitHub error (${resp.status}): ${errBody.message || resp.statusText}`);
  }
  const repoData = await resp.json();
  const canPush = Boolean(repoData.permissions?.push);
  return {
    ok: true,
    fullName: repoData.full_name,
    defaultBranch: repoData.default_branch,
    canPush
  };
}

chrome.runtime.onInstalled.addListener(async () => {
  const existing = await chrome.storage.local.get(["settings"]);
  if (!existing.settings) {
    await chrome.storage.local.set({ settings: DEFAULT_SETTINGS });
  }
});

chrome.runtime.onMessage.addListener((message, _sender, sendResponse) => {
  if (!message || !message.type) return;

  if (message.type === "PUSH_SUBMISSION") {
    pushToGitHub(message.payload)
      .then((res) => sendResponse(res))
      .catch((err) => sendResponse({ ok: false, error: err.message }));
    return true;
  }

  if (message.type === "TEST_CONNECTION") {
    testGitHubConnection(message.settings)
      .then((res) => sendResponse(res))
      .catch((err) => sendResponse({ ok: false, error: err.message }));
    return true;
  }

  if (message.type === "FETCH_CF_STATUS") {
    const handle = encodeURIComponent(message.handle);
    const count = message.count || 10;
    fetch(`https://codeforces.com/api/user.status?handle=${handle}&from=1&count=${count}`)
      .then((r) => r.json())
      .then((json) => {
        if (json.status !== "OK") {
          throw new Error(json.comment || "Codeforces API error");
        }
        sendResponse({ ok: true, submissions: json.result });
      })
      .catch((err) => sendResponse({ ok: false, error: err.message }));
    return true;
  }
});
