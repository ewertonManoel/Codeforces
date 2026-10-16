#include <bits/stdc++.h>

using namespace std;

#define pb push_back
const int INF = 1e8 + 7;
using pii = pair<int, int>;

vector<vector<int>> edges;
vector<vector<int>> adj;
vector<int> colors;

bool dfs(int u, bool c) {
    colors[u] = c;
    for(auto v : adj[u]) {
        if(colors[v] == -1) {
            if(dfs(v, !c)) return true;
        }
        else {
            if(colors[v] == c) return true;
            continue;
        }
    }
    return false;
}
void solve() {
    int n, m; cin >> n >> m;
    vector<pii> edges(m, pii());
    adj.assign(m, vector<int>());
    colors.assign(m, -1);  
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if(a > b) swap(a, b);
        edges[i] = {a, b};
    }
    for(int i = 0; i < m; i++) {
        int l = edges[i].first, r = edges[i].second;
        for(int j = i + 1; j < m; j++) {
            int l2 = edges[j].first, r2 = edges[j].second;
            if(l2 < l && r2 > l && r2 < r || l2 > l && l2 < r && r2 > r) {
                adj[i].pb(j);
                adj[j].pb(i);
            }
        }
    }
    bool possible = true;
    for(int i = 0; i < m; i++) {
        if(colors[i] != -1) continue;
        if(dfs(i, 0)) {
            possible = false;
            break;
        }
    }
    if(possible) {
        for(int i = 0; i < m; i++) {
            if(colors[i] == 1) cout << 'o';
            else cout << 'i';
        }
    }
    else cout << "Impossible";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}