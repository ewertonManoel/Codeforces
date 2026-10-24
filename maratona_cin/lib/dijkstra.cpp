#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w; u--; v--;
        adj[u].push_back({v, w});
    }

    vector<ll> dist(n, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}