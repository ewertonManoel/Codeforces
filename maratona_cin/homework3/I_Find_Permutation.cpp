#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

vector<vector<int>> adj;
vector<int> indegree;
vector<int> ans;
void solve() {
    int n, m; cin >> n >> m;
    adj.assign(n, vector<int>());
    indegree.assign(n, 0);
    ans.assign(n, 0);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        indegree[b]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) if(indegree[i] == 0) q.push(i);
    bool ok = true;
    int number = 1;
    while(!q.empty()) {
        if(q.size() > 1) {
            bool ok = false;
            break;
        }
        int u = q.front(); q.pop();
        ans[u] = number++;
        for(auto v : adj[u]) {
            indegree[v]--;
            if(indegree[v] == 0) q.push(v);
        }
    }
    if(!ok) while(!q.empty()) q.pop();
    if(number - 1 < n) {
        cout << "No" << '\n';
    }
    else {
        cout << "Yes" << '\n';
        for(int i : ans) cout << i << " ";
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}