#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

vector<vector<int>> adj;
vector<int> visited;
int steps, loop_steps;

int dfs(int u) {
    visited[u] = ++steps;
    for(auto v : adj[u]) {
        if(v == -1) return 1;
        if(visited[v] != -1) {
            loop_steps = steps - visited[v] + 1;
            steps -= loop_steps;
            return 2;
        }
        int ret = dfs(v);
        if(ret != 0) return ret;
    }
    return 0;
}

void solve() {
    while(true) {
        int n, m, start; cin >> n >> m >> start;
        if(n == 0 && m == 0 && start == 0) return;
        start--;
        adj.assign(n * m, vector<int>());
        visited.assign(n * m, -1);
        steps = loop_steps = 0;
        for(int i = 0; i < n * m; i++) {
            char c; cin >> c;
            int idx = i;
            if(c == 'N') idx -= m;
            else if(c == 'S') idx += m;
            else if(c == 'W') idx--;
            else idx++;
            if((i % m == 0 && c == 'W') || ((i + 1) % m == 0 && c == 'E') || (i / m == 0 && c == 'N') || (i / m == n - 1 && c == 'S')) idx = -1; 
            adj[i].pb(idx); 
        }
        if(dfs(start) == 1) {
            cout << steps << " step(s) to exit" << '\n';
        }
        else {
            cout << steps << " step(s) before a loop of "<< loop_steps << " step(s)" << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}