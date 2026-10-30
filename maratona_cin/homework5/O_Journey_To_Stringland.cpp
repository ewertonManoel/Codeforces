#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 1e18;

vector<vector<vector<ll>>> memo;
string s; int n, k;

ll dp(int l, int r, int sz) {
    if(sz == k) return 0;
    if(r - l + 1 + sz < k) return INF;
    if(l > r) return INF;
    if(memo[l][r][sz] != INF) return memo[l][r][sz];
    if(l == r) return memo[l][r][sz] = dp(l + 1, r, sz + 1);
    return memo[l][r][sz] = min({dp(l + 1, r, sz), dp(l, r - 1, sz), (s[r] == s[l] ? 0 : 1) + dp(l + 1, r - 1, sz + 2)});
}
void solve() {
    cin >> n >> k >> s;
    memo.assign(n, vector<vector<ll>>(n, vector<ll>(k + 1, INF)));
    cout << dp(0, n-1, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}