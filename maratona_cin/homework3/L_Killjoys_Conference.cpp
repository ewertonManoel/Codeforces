#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

vector<vector<int>> adj;
vector<int> color;

bool dfs(int u, int p, bool c) {
    color[u] = c;
    for(auto v : adj[u]) {
        if(v == p) continue;
        if(color[v] == -1) {
            if(dfs(v, u, !c)) return true;
        }
        else if(color[v] == color[u]) return true;
    }
    return false;
}

void solve() {
    int n, m; ll p; cin >> n >> m >> p;
    adj.assign(n, vector<int>());
    color.assign(n, -1);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int count = 0;
    for(int u = 0; u < n; u++) {
        if(color[u] == -1) {
            count++;
            if(dfs(u, -1, 0)) {
                cout << "impossible" << '\n';
                return;
            }
        }
    }
    ll ans = 1;
    for(int i = 0; i < count - 1; i++) {
        ans = (ans << 1) % p; 
    }
    ans = (ans + 1) % p;
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 
