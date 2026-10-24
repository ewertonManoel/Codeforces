#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18

void solve() {
    int n, m; cin >> n >> m;
    vector<tuple<int, int, ll>> edges(m);
    for (int i = 0; i < m; ++i) {
        int u, v; ll w; cin >> u >> v >> w; u--; v--;
        edges[i] = {u, v, w};
    }

    vector<ll> dist(n, INF);
    dist[0] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) {
            break;
        }
    }

    bool has_negative_cycle = false;
    for (auto [u, v, w] : edges) {
        if (dist[u] < INF && dist[u] + w < dist[v]) {
            has_negative_cycle = true;
            break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}