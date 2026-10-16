#include <bits/stdc++.h>

using namespace std;

#define pb push_back
const int INF = 1e8 + 7;
using pii = pair<int, int>;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> cities(n, vector<int>());
    vector<string> holidays(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        cities[a].pb(b);
        cities[b].pb(a);
    }
    int w; cin >> w;
    for(int i = 0; i < n; i++) {
        cin >> holidays[i];
    }
    vector<vector<vector<pii>>> adj(n, vector<vector<pii>>(w, vector<pii>()));
    vector<vector<int>> indegree(n, vector<int>(w, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < w; j++) {
            if(holidays[i][j] == 'o') {
                for(auto v : cities[i]) {
                    if(holidays[v][(j + 1) % w] == 'o') {
                        adj[i][j].pb({v, (j + 1) % w});
                        indegree[v][(j + 1) % w]++;
                    }
                }
                if(holidays[i][(j + 1) % w] == 'o') {
                    adj[i][j].pb({i, (j + 1) % w});
                    indegree[i][(j + 1) % w]++;
                }
            }
        }
    }
    queue<pii> q;
    for(int i = 0; i < n; i++) for(int j = 0; j < w; j++) {
        if(indegree[i][j] == 0) q.push({i, j});
    }
    int op = 0;
    while(!q.empty()) {
        auto [a, b] = q.front(); q.pop();
        for(auto v : adj[a][b]) {
            indegree[v.first][v.second]--;
            if(indegree[v.first][v.second] == 0) {
                q.push({v.first, v.second});
            }
        }
        op++;
    }
    if(op < n * w) cout << "Yes" << '\n';
    else cout << "No" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; cin >> t; while(t--) { solve(); }
}