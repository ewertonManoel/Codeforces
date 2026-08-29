#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

vector<vector<int>> tree;
vector<int> height;

int dfs(int u, int p) {
    int h = 0;
    for(auto& v : tree[u]) {
        if(v != p) h = max(h, dfs(v, u));
    }
    height[u] = 1 + h; return height[u];
}
void dfs2(int u, int p, int& ans) {
    int maximum = 0;
    int secMaximum = 0;
    for(auto& v : tree[u]) {
        if(v == p) continue;
        dfs2(v, u, ans);
        if(height[v] > maximum) {
            secMaximum = maximum;
            maximum = height[v];
        }
        else secMaximum = max(secMaximum, height[v]);
    }
    ans += secMaximum + 1;
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        tree.assign(n + 1, vector<int>());
        height.assign(n + 1, 0);
        for(int i = 2; i <= n; i++) {
            int x; cin >> x;
            tree[i].pb(x);
            tree[x].pb(i);
        }
        int ans = 0;
        dfs(1, -1);
        dfs2(1, -1, ans);
        cout << ans << '\n';
    }
}