#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

vector<vector<ll>> memo;
vector<ll> a, b, c;
int n;

ll dp(int i, int r) {
    if(i == n) return 0;
    if(memo[i][r] != -1) return memo[i][r];
    ll first = (r != 0) ? a[i] + dp(i + 1, 0) : 0;
    ll second = (r != 1) ? b[i] + dp(i + 1, 1) : 0;
    ll third = (r != 2) ? c[i] + dp(i + 1, 2) : 0;
    return memo[i][r] = max({first, second, third});
}

void solve() {
    cin >> n;
    memo.assign(n, vector<ll>(4, -1));
    a.assign(n, 0); b.assign(n, 0); c.assign(n, 0);
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
    cout << dp(0, 3) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}