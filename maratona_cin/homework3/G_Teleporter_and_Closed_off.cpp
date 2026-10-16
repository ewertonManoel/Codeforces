#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

const int INF = 1e8 + 7;

auto bfs(int s, vector<vector<int>>& adj) {
    queue<int> q;
    q.push(s);
    vector<int> distances(adj.size(), INF);
    distances[s] = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v : adj[u]) {
            if(distances[v] == INF) {
                distances[v] = distances[u] + 1;
                q.push(v);
            }
        }
    }
    return distances;
}
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n, vector<int>());
    vector<vector<int>> adj_rev(n, vector<int>());

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 1; j <= m; j++) {
            if(s[j-1] == '1') {
                adj[i].pb(i + j);
                adj_rev[i + j].pb(i);
            }
        }
    }
    vector<int> dist_begin = bfs(0, adj);
    vector<int> dist_end = bfs(n - 1, adj_rev);
    for(int k = 1; k < n - 1; k++) {
        int ans = INF;
        for(int idx1 = max(0, k - m + 1); idx1 < k; idx1++) {
            for(int idx2 : adj[idx1]) {
                if(idx2 <= k) continue;
                ans = min(ans, dist_begin[idx1] + dist_end[idx2] + 1);
            }
        }
        if(ans == INF) ans = -1;
        cout << ans << " ";
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 
