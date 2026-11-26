// Problem: 105535K - Know Your Duration of Stay
// Contest: 105535
// Language: C++20 (GCC 13-64) | Time: 156 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105535/problem/K
// Submission: https://codeforces.com/gym/105535/submission/399845628

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> months(n, 0);
    vector<ll> psum(n+1, 0);
    for(int i = 0; i < n; i++) cin >> months[i];
    for(int i = 0; i < n; i++) psum[i+1] = psum[i] + months[i];
    for(int i = 0; i < m; i++) {
        ll di, mi, df, mf; cin >> di >> mi >> df >> mf;
        ll ans = -di + df + 1;
        if(mf < mi || (mf == mi && df < di)) ans += psum[n] - psum[mi-1] + psum[mf-1];
        else ans += psum[mf-1] - psum[mi-1];
        cout << ans << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t; while(t--) solve();
}
