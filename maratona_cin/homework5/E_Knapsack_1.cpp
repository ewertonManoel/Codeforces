#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int n, w;
vector<vector<ll>> dp;
vector<pll> items;

ll knapsack(int i, int cap) {
    if(i == n) return 0;
    if(dp[i][cap] != -1) return dp[i][cap];
    auto [w, v] = items[i];
    ll take = (cap - w >= 0) ? v + knapsack(i+1, cap - w) : 0;
    ll n_take = knapsack(i + 1, cap);
    return dp[i][cap] = max(take, n_take);
}

void solve() {
    cin >> n >> w;
    dp.assign(n, vector<ll>(w + 1, -1));
    items.resize(n);
    for(int i = 0; i < n; i++) cin >> items[i].first >> items[i].second;
    cout << knapsack(0, w) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}