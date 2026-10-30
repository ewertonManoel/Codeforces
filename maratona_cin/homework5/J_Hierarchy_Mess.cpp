#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e9;
const ll MOD = 998244353;
#define pb push_back

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<ll> dp(n, 1);
    dp[0] = 0;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[b].pb(a);
    }
    queue<int> q;
    vector<int> indegree(n, 0);
    for(int u = 0; u < n; u++) {
        for(auto v : adj[u]) indegree[v]++;
    }
    for(int u = 0; u < n; u++) {
        if(indegree[u] == 0) q.push(u);
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v : adj[u]) {
            indegree[v]--;
            dp[v] = (dp[v] + dp[u]) % MOD;
            if(indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << dp[0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}