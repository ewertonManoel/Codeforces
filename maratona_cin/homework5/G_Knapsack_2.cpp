#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX_SZ = 1e5 + 5;
const ll INF = 1e18 + 7;

void solve() {
    int n, cap_i; cin >> n >> cap_i;
    vector<pll> items(n);
    for(int i = 0; i < n; i++) cin >> items[i].first >> items[i].second;

    vector<vector<ll>> dp(n + 1, vector<ll>(MAX_SZ, INF));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        auto [w, v] = items[i];
        for(int j = 0; j < MAX_SZ; j++) {
            if(dp[i][j] == INF) continue;
            dp[i+1][j] = min(dp[i+1][j], dp[i][j]);
            if(j + v < MAX_SZ) dp[i+1][j+v] = min(dp[i+1][j+v], dp[i][j] + w);
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++) for(int j = 0; j < MAX_SZ; j++) {
        if(dp[i][j] <= cap_i) ans = max(ans, j);
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}