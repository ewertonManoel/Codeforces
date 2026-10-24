#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18

struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(n), sz(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    void join(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
    }
    bool check(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n, m; cin >> n >> m;
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        dsu.join(u, v);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}