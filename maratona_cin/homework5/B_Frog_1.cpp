#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> dp(n, 0);
    vector<int> heights(n, 0);
    for(int i = 0; i < n; i++) cin >> heights[i];
    dp[0] = 0; dp[1] = abs(heights[1] - heights[0]);
    for(int i = 2; i < n; i++) {
        dp[i] = min(dp[i-2] + abs(heights[i] - heights[i-2]), dp[i-1] + abs(heights[i] - heights[i-1]));
    }
    cout << dp[n-1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}