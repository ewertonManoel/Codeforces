// Problem: 105811J - Security Breach
// Contest: 105811
// Language: C++20 (GCC 13-64) | Time: 125 ms | Memory: 4600 KB
// Problem Link: https://codeforces.com/gym/105811/problem/J
// Submission: https://codeforces.com/gym/105811/submission/399719785

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 1e18;
using pll = pair<ll, ll>;

bool dijkstra(vector<pll> sources, vector<vector<pll>>& adj) {
    int n = adj.size();
    vector<ll> dist(n, INF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    for(auto &p : sources) {
        auto [s, k] = p;
        dist[s] = k;
        pq.push({k, s});
    }

    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        bool b = (u == 0);
        for(auto [v, w] : adj[u]) {
            if(w <= dist[u]) b = true;
            if(max(dist[u], w) >= dist[v]) continue;
            dist[v] = max(dist[u], w);
            pq.push({dist[v], v});
        }
        if(!b) return false;
    }
    return true;
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pll>> adj(n);
    for(int i = 0; i < m; i++) {
        ll a, b, c; cin >> a >> b >> c; a--; b--;
        adj[a].push_back({b, c});
    }
    if(adj[0].size() == 0) {
        cout << "YES\n";
        return;
    }
    vector<pll> sources;
    for(auto p : adj[0]) {
        sources.push_back(p);
    }
    if(dijkstra(sources, adj)) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
