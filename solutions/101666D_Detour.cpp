// Problem: 101666D - Detour
// Contest: 101666
// Language: C++20 (GCC 13-64) | Time: 109 ms | Memory: 7000 KB
// Problem Link: https://codeforces.com/gym/101666/problem/D
// Submission: https://codeforces.com/gym/101666/submission/399823538

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 1e18;

vector<int> dijkstra(int src, vector<vector<pll>>& adj) {
    int n = adj.size();
    vector<ll> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        
        for(auto [v, w] : adj[u]) {
            if(dist[u] + w >= dist[v]) continue;
            parent[v] = u;
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
    return parent;
}

pair<int, vector<int>> bfs(vector<vector<int>>& adj, vector<int>& dont_go) {
    int n = adj.size();
    vector<int> dist(n, -1);
    vector<int> parent(n, -1);
    queue<int> q;
    dist[0] = 0;
    q.push(0);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(dist[v] != -1) continue;
            if(dont_go[u] == v) continue;
            parent[v] = u;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return {dist[1], parent};
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pll>> adj(n);
    vector<vector<int>> simple_adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; ll c; cin >> a >> b >> c;
        adj[a].emplace_back(b, c);
        adj[b].emplace_back(a, c);
        simple_adj[a].push_back(b);
        simple_adj[b].push_back(a);
    }
    vector<int> parent = dijkstra(1, adj);
    auto [sz, path] = bfs(simple_adj, parent);
    if(sz == -1) {
        cout << "impossible\n";
        return;
    }
    cout << sz + 1 << " ";
    vector<int> ans;
    int cur = 1;
    while(cur != -1) {
        ans.push_back(cur);
        cur = path[cur];
    }
    reverse(ans.begin(), ans.end());
    for(int i : ans) cout << i << " ";
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
