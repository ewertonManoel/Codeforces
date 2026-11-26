// Problem: 104945J - Olympic goodies
// Contest: 104945
// Language: C++20 (GCC 13-64) | Time: 78 ms | Memory: 4500 KB
// Problem Link: https://codeforces.com/gym/104945/problem/J
// Submission: https://codeforces.com/gym/104945/submission/399845411

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> adj;

void dfs(int u, int p, int &cnt) {
    if(adj[u].size() == 1) cnt++;
    for(auto v : adj[u]) {
        if(v == p) continue;
        dfs(v, u, cnt);
    }
}

void solve() {
    int n, p; cin >> n >> p;
    adj.resize(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if(n == 1) {
        cout << p << '\n';
        return;
    }
    int cnt = 0;
    dfs(0, -1, cnt);
    int val = (p / cnt) * 2;
    if(p % cnt == 1) val++;
    else if(p % cnt >= 2) val += 2;
    cout << val << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
