#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

vector<vector<int>> tree;
vector<pii> values;

int mod(int a, int b) {return (((a % b) + b) % b);}

bool dfs(int u, int p) {
    for(auto& v : tree[u]) {
        if(!dfs(v, u)) return false;
    }
    int min_idx = 0;
    int minimum = INF;
    int maximum = -INF;
    int n = tree[u].size();
    for(int i = 0; i < n; i++) {
        int cur = tree[u][i];
        if(values[cur].first < minimum) {
            minimum = values[cur].first;
            min_idx = i;
        }
        maximum = max(maximum, values[cur].second);
    }
    if(n > 1) for(int i = (min_idx + 1) % n; i != min_idx; i = (i + 1) % n) {
        if(values[tree[u][i]].first <= values[tree[u][mod(i-1, n)]].second) return false;
    }
    if(n > 0) values[u] = {minimum, maximum};
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        tree.assign(n, vector<int>());
        values.assign(n, pii());
        int root = 0;
        for(int i = 1; i < n; i++) {
            int x; cin >> x; x--;
            tree[x].pb(i);
        }
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            if(x != 0) values[i] = {x, x};
            else values[i] = {INF, -INF};
        }
        if(dfs(root, -1)) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

/*
5
4 4 1 3
0 1 0 0 2
*/