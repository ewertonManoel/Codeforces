#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

vector<int> visited;
vector<vector<int>> graph;

void dfs(int u, int prevColor, int& red, int& blue, bool& valid) {
    int color = 1 - prevColor;
    visited[u] = color;
    (color == 0 ? red++ : blue++);
    for(auto& v : graph[u]) {
        if(visited[v] == color) valid = false;
        if(visited[v] == -1) dfs(v, color, red, blue, valid);
    }
}
int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int m; cin >> m;
        graph.assign(n + 1, vector<int>());
        visited.assign(n + 1, -1);
        for(int i = 0; i < m; i++) {
            int u; cin >> u;
            int v; cin >> v;
            graph[u].pb(v);
            graph[v].pb(u);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++) {
            if(visited[i] == -1) {
                int red = 0, blue = 0;
                bool valid = true;
                dfs(i, 0, red, blue, valid);
                if(valid) ans += max(red, blue);
            }
        }
        cout << ans << '\n';
    }
}