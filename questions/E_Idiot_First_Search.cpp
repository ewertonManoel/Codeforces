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
vector<int> weights;

void dfs1(int u, int p) {
    for(int v : tree[u]) {
        if(v == p) continue;
        dfs1(v, u);
        weights[u] = (weights[u] + weights[v] + 2) % MOD;
    }
}

void dfs2(int u, int p) {
    for(int v : tree[u]) {
        if(v == p) continue;
        weights[v] = (weights[v] + weights[u]) % MOD;
        dfs2(v, u);
    }
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        tree.clear();
        tree.resize(n + 1);
        weights.assign(n + 1, 0);
        tree[0].pb(1);
        tree[1].pb(0);
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            int y; cin >> y;
            if(x != 0) {
                tree[i].pb(x);
                tree[i].pb(y);
                tree[x].pb(i);
                tree[y].pb(i);
            }
        }
        dfs1(0, -1);
        for(int &i : weights) i = (i + 1) % MOD;
        weights[0] = 0;
        dfs2(0, -1);
        for(int i = 1; i < weights.size(); i++) cout << weights[i] << " ";
        cout << '\n';
    }
}