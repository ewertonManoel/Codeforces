#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define INF 1e18
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<ll> dp(n+1, 0);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 6 && i - j >= 0; j++) {
            dp[i] = (dp[i] + dp[i-j]) % MOD;
        }
    }
    cout << dp[n] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}