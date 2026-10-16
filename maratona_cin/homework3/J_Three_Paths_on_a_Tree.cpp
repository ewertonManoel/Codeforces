#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

const int INF = 1e8 + 7;

set<pii> st;
vector<vector<int>> adj;
int dist, node;

void dfs(int u, int p = -1, int d = 0) {
    if(d > dist) {
        dist = d;
        node = u;
    }
    for(auto v : adj[u]) {
        if(v == p) continue;
        dfs(v, u, d + 1);
    }
}

bool find(int u, const int target, int p = -1) {
    if(u == target) return true;
    for(auto v : adj[u]) {
        if(v == p) continue;
        if(find(v, target, u)) {
            if(u > v) swap(u, v);
            st.insert({u, v});
            return true;
        }
    }
    return false;
}

void solve() {
    int n; cin >> n;
    adj.assign(n, vector<int>());
    st.clear();
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int a, b, c;
    node = dist = 0;
    dfs(0);
    a = node;
    node = dist = 0;
    dfs(a);
    b = node;
    node = dist = 0;
    queue<int> q;
    vector<int> distances(n, INF);
    find(a, b);
    for(auto p : st) {
        distances[p.first] = 0;
        distances[p.second] = 0;
    }
    for(int i = 0; i < n; i++) {
        if(distances[i] == 0) {
            q.push(i);
            if(i != a && i != b) c = i;
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v : adj[u]) {
            if(distances[v] == INF) {
                distances[v] = distances[u] + 1;
                q.push(v);
                c = v;
            }
        }
    }
    find(a, c);
    find(b, c);
    cout << st.size() << '\n';
    cout << a + 1 << " " << b + 1 << " " << c + 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 
