#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<string> grid(n);
    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for(int i = 0; i < n; i++) cin >> grid[i];
    dp[0][0] = 1;
    if(grid[0][0] == '*') dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(grid[i][j] == '*') continue;
            if(i == 0 && j == 0) continue;
            ll up = (i-1 >= 0 && grid[i-1][j] == '.') ? dp[i-1][j] : 0;
            ll left = (j-1 >= 0 && grid[i][j-1] == '.') ? dp[i][j-1] : 0;
            dp[i][j] = (up + left) % MOD;
        }
    }
    cout << dp[n-1][n-1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}