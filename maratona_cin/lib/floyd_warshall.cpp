```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v; ll w; cin >> u >> v >> w; u--; v--;
        dist[u][v] = min(dist[u][v], w);
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}