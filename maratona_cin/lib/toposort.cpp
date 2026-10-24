#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define INF 1e18

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }

    bool has_cycle = (order.size() < n);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}