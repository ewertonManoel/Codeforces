#include <bits/stdc++.h>

#define pb push_back
using namespace std;
using ll = long long;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    for(auto v : adj[u]) {
        if(visited[v]) continue;
        dfs(v);
    }
}

void solve() {
    int n, m; cin >> n >> m;
    adj.assign(n, vector<int>());
    visited.assign(n, false);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    vector<int> roads;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            roads.pb(i);
            dfs(i);
        }
    }
    int edges = roads.size() - 1;
    cout << edges << '\n';
    for(int i = 0; i < edges; i++) {
        cout << roads[i] + 1 << " " << roads[i + 1] + 1 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}