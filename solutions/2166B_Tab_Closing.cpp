// Problem: 2166B - Tab Closing
// Contest: 2166 | Rating: 900 | Tags: math
// Language: C++20 (GCC 13-64) | Time: 46 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/2166/problem/B
// Submission: https://codeforces.com/contest/2166/submission/399705915

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll a, b, n; cin >> a >> b >> n;
    if(n * b <= a || b >= a) cout << 1 << '\n';
    else cout << 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; cin >> t; while(t--) solve();
}
