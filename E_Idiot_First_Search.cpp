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

void bfs(vector<int>& adj, vector<int>& weights, queue<int>& q) {
    vector<bool> visited(weights.size(), false);
    while(!q.empty()) {
        int index = q.front();
        q.pop();
        int neighbor = adj[index];
        weights[neighbor] = (weights[neighbor] + weights[index] + 2) % MOD;
        if(!visited[neighbor]) visited[neighbor] = true;
        else q.push(neighbor);
    }
    for(int &i : weights) i = (i + 1) % MOD;
    weights[0] = 0;
}

void dfs(vector<vector<int>>& tree, vector<int>& weights, int i) {
    for(int j : tree[i]) {
        weights[j] = (weights[j] + weights[i]) % MOD;
        dfs(tree, weights, j);
    }
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> adj(n + 1);
        vector<vector<int>> tree(n + 1);
        vector<int> weights(n + 1, 0);
        queue<int> leaves;
        adj[1] = 0;
        tree[0].pb(1);
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            int y; cin >> y;
            if(x != 0) {
                tree[i].pb(x);
                tree[i].pb(y);
                adj[x] = i;
                adj[y] = i;
            }
            else leaves.push(i);
        }
        bfs(adj, weights, leaves);
        dfs(tree, weights, 1);
        for(int i = 1; i < weights.size(); i++) cout << weights[i] << " ";
        cout << '\n';
    }
}