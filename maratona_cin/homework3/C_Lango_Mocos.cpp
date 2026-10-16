#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

vector<vector<int>> adj;
vector<int> color;

bool dfs(int u, int p, int c) {
    color[u] = c;
    for(auto v : adj[u]) {
        if(v == p) continue;
        if(color[v] != -1) {
            if(color[v] == c) return true;
            continue;
        }
        if(dfs(v, u, !c)) return true;
    }
    return false;
}

void solve() {
    int n, m; cin >> n >> m;
    adj.assign(n, vector<int>());
    color.assign(n, -1);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    for(int i = 0; i < n; i++) {
        if(color[i] != -1) continue;
        if(dfs(i, -1, 0)) {
            cout << "IMPOSSIVEL" << '\n';
            return;
        }
    }
    int num = count(color.begin(), color.end(), 0);
    cout << "POSSIVEL" << '\n' << num << " " << n - num << '\n';
    for(int i = 0; i < n; i++) if(color[i] == 0) cout << i + 1 << ' ';
    cout << '\n';
    for(int i = 0; i < n; i++) if(color[i] == 1) cout << i + 1 << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}