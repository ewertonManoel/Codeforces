// Problem: 131C - The World is a Theatre
// Contest: 131 | Rating: 1400 | Tags: combinatorics, math
// Language: C++20 (GCC 13-64) | Time: 62 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/131/problem/C
// Submission: https://codeforces.com/contest/131/submission/399819101

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll nCr(ll n, ll r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n - r) r = n - r;

    ll res = 1;
    for (ll i = 1; i <= r; i++) {
        res = res * (n - r + i) / i;
    }
    return res;
}

void solve() {
    ll n, m, t; cin >> n >> m >> t;
    ll comb = 0;
    for(int i = 4; i <= n; i++) {
        if(t - i < 1) continue;
        comb += nCr(n, i) * nCr(m, t - i);
    }
    cout << comb << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    solve();
}
