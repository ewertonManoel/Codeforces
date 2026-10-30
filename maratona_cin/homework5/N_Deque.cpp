#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;
int n;
vector<vector<vector<ll>>> memo;
vector<ll> values;

ll dp(int l, int r, bool turn) {
    if(l > r) return 0;
    if(memo[l][r][turn] != -1) return memo[l][r][turn];
    if(turn) return memo[l][r][turn] = max(values[l] + dp(l+1, r, !turn), values[r] + dp(l, r-1, !turn));
    else return memo[l][r][turn] = min(-values[l] + dp(l+1, r, !turn), -values[r] + dp(l, r-1, !turn));
}
void solve() {
    cin >> n;
    memo.assign(n, vector<vector<ll>>(n, vector<ll>(2, -1)));
    values.assign(n, 0);
    for(int i = 0; i < n; i++) cin >> values[i];
    cout << dp(0, n-1, true) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}