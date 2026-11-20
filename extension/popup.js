const DEFAULT_SETTINGS = {
  enabled: true,
  handle: "ewerton",
  repo: "ewertonManoel/Codeforces",
  branch: "main",
  folder: "solutions",
  token: "",
  addHeader: true
};

const els = {
  form: document.getElementById("settings-form"),
  enabled: document.getElementById("enabled"),
  handle: document.getElementById("handle"),
  repo: document.getElementById("repo"),
  branch: document.getElementById("branch"),
  folder: document.getElementById("folder"),
  token: document.getElementById("token"),
  addHeader: document.getElementById("addHeader"),
  saveBtn: document.getElementById("save-btn"),
  syncNowBtn: document.getElementById("sync-now-btn"),
  statusBox: document.getElementById("status-box"),
  historyList: document.getElementById("history-list")
};

function showStatus(msg, type = "info") {
  els.statusBox.textContent = msg;
  els.statusBox.className = `status ${type}`;
}

function renderHistory(history) {
  els.historyList.innerHTML = "";
  if (!Array.isArray(history) || history.length === 0) {
    const li = document.createElement("li");
    li.className = "empty";
    li.textContent = "Nenhuma sincronização ainda.";
    els.historyList.appendChild(li);
    return;
  }

  for (const item of history.slice(0, 8)) {
    const li = document.createElement("li");
    const a = document.createElement("a");
    a.href = item.htmlUrl || "#";
    a.target = "_blank";
    a.rel = "noopener noreferrer";
    a.textContent = item.problemLabel || item.filePath;
    a.title = item.filePath;

    const badge = document.createElement("span");
    badge.className = "badge";
    badge.textContent = item.status === "updated" ? "updated" : item.status === "unchanged" ? "ok" : "synced";

    li.appendChild(a);
    li.appendChild(badge);
    els.historyList.appendChild(li);
  }
}

function readFormSettings() {
  return {
    enabled: els.enabled.checked,
    handle: els.handle.value.trim(),
    repo: els.repo.value.trim(),
    branch: els.branch.value.trim() || "main",
    folder: els.folder.value.trim() || "solutions",
    token: els.token.value.trim(),
    addHeader: els.addHeader.checked
  };
}

async function loadState() {
  const data = await chrome.storage.local.get(["settings", "syncHistory"]);
  const s = { ...DEFAULT_SETTINGS, ...(data.settings || {}) };

  els.enabled.checked = Boolean(s.enabled);
  els.handle.value = s.handle || "";
  els.repo.value = s.repo || "";
  els.branch.value = s.branch || "main";
  els.folder.value = s.folder || "solutions";
  els.token.value = s.token || "";
  els.addHeader.checked = s.addHeader !== false;

  renderHistory(data.syncHistory);
}

els.enabled.addEventListener("change", async () => {
  const settings = readFormSettings();
  await chrome.storage.local.set({ settings });
  showStatus(settings.enabled ? "Auto-sync ativado." : "Auto-sync pausado.", "info");
});

els.form.addEventListener("submit", async (e) => {
  e.preventDefault();
  const settings = readFormSettings();
  await chrome.storage.local.set({ settings });

  if (!settings.token) {
    showStatus("Configurações salvas. Cole seu GitHub Token para ativar o envio.", "info");
    return;
  }

  els.saveBtn.disabled = true;
  showStatus("Testando conexão com o GitHub...", "info");

  try {
    const res = await chrome.runtime.sendMessage({
      type: "TEST_CONNECTION",
      settings
    });
    if (!res || !res.ok) {
      throw new Error(res?.error || "Falha ao conectar no GitHub.");
    }
    if (!res.canPush) {
      showStatus(`Conectado a ${res.fullName}, mas o token não tem permissão de escrita (Contents: Read & write).`, "err");
    } else {
      showStatus(`Conectado com sucesso a ${res.fullName}! Pronto para sincronizar novas submissões Accepted.`, "ok");
    }
  } catch (err) {
    showStatus(err.message, "err");
  } finally {
    els.saveBtn.disabled = false;
  }
});

els.syncNowBtn.addEventListener("click", async () => {
  els.syncNowBtn.disabled = true;
  showStatus("Buscando última submissão Accepted na aba do Codeforces...", "info");

  try {
    const [tab] = await chrome.tabs.query({ active: true, currentWindow: true });
    if (!tab || !tab.id || !tab.url || !tab.url.startsWith("https://codeforces.com/")) {
      throw new Error("Abra qualquer página do codeforces.com na aba ativa para usar o Sync manual.");
    }

    const res = await chrome.tabs.sendMessage(tab.id, { type: "SYNC_LATEST_ACCEPTED" });
    if (!res || !res.ok) {
      throw new Error(res?.error || "Falha ao sincronizar.");
    }

    showStatus(`Sincronizado: ${res.filePath}`, "ok");
    const data = await chrome.storage.local.get(["syncHistory"]);
    renderHistory(data.syncHistory);
  } catch (err) {
    showStatus(err.message, "err");
  } finally {
    els.syncNowBtn.disabled = false;
  }
});

loadState();
