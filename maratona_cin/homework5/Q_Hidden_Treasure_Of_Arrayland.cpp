#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 1e18;

void solve() {
    int n, k, inv; cin >> n >> k; inv = 2 * k;
    vector<ll> values(n, 0);
    vector<vector<ll>> dp(inv + 1, vector<ll>(2, 0));
    vector<vector<ll>> nxt_dp(inv + 1, vector<ll>(2, 0));
    for(int i = 0; i < n; i++) cin >> values[i];
    for(int i = n-1; i >= 0; i--) {
        for(int j = inv; j >= 0; j--) {
            int signal = (j % 2 == 0) ? 1 : -1;
            dp[j][1] = max({0LL, signal * values[i] + nxt_dp[j][1], (j == 0) ? 0LL : -signal * values[i] + nxt_dp[j - 1][1]});
            dp[j][0] = max({nxt_dp[j][0], values[i] + nxt_dp[j][1], (j == 0) ? 0LL : -values[i] + nxt_dp[j - 1][1]});
        }
        nxt_dp = dp;
    }
    ll ans = -INF;
    for(int j = 0; j <= inv; j++) ans = max({ans, dp[j][0], dp[j][1]});
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}