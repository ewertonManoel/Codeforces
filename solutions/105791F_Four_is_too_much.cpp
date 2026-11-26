// Problem: 105791F - Four is too much
// Contest: 105791
// Language: C++20 (GCC 13-64) | Time: 46 ms | Memory: 5100 KB
// Problem Link: https://codeforces.com/gym/105791/problem/F
// Submission: https://codeforces.com/gym/105791/submission/399847451

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int n, w;
vector<vector<ll>> dp;
vector<pll> items;
const ll LINF = 1e18;

ll knapsack(int i, int cap) {
    if(cap <= 0) return 0;
    if(i == n) return LINF;
    if(dp[i][cap] != -1) return dp[i][cap];
    auto [w, v] = items[i];
    ll take = v + knapsack(i+1, cap - w);
    ll n_take = knapsack(i + 1, cap);
    return dp[i][cap] = min(take, n_take);
}

void solve() {
    cin >> w >> n;
    dp.assign(n, vector<ll>(w + 1, -1));
    items.resize(n);
    for(int i = 0; i < n; i++) cin >> items[i].first >> items[i].second;
    ll val = knapsack(0, w); 
    if(val == LINF) cout << -1 << '\n';
    else cout << val << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}
