#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define INF 1e18

vector<vector<int>> adj;
vector<int> color;

bool dfs(int u, int p, int c) {
    color[u] = c;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (color[v] != -1) {
            if (color[v] == c) return true;
            continue;
        }
        if (dfs(v, u, !c)) return true;
    }
    return false;
}

void solve() {
    int n, m; cin >> n >> m;
    adj.assign(n, vector<int>());
    color.assign(n, -1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    bool is_bipartite = true;
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue;
        if (dfs(i, -1, 0)) {
            is_bipartite = false;
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}