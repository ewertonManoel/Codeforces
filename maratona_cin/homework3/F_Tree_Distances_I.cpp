#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

vector<vector<int>> adj;
vector<int> distances;
int max_dist;
void dfs(int u, int p, int d, int &node) {
    if(d > max_dist) {
        max_dist = d;
        node = u;
    }
    for(auto v : adj[u]) {
        if(v == p) continue;
        dfs(v, u, d + 1, node);
    }
}

void found_dist(int u, int p, int d) {
    distances[u] = max(distances[u], d);
    for(auto v : adj[u]) {
        if(v == p) continue;
        found_dist(v, u, d + 1);
    }
}

void solve() {
    int n; cin >> n;
    adj.assign(n, vector<int>());
    distances.assign(n, 0);
    for(int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int node = 0, node2 = 0;
    max_dist = 0;
    dfs(0, -1, 0, node);
    max_dist = 0;
    dfs(node, -1, 0, node2);
    found_dist(node, -1, 0);
    found_dist(node2, -1, 0);
    for(int i = 0; i < n; i++) cout << distances[i] << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}