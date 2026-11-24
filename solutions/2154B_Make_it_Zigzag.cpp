// Problem: 2154B - Make it Zigzag
// Contest: 2154 | Rating: 1000 | Tags: constructive algorithms, greedy
// Language: C++20 (GCC 13-64) | Time: 62 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/2154/problem/B
// Submission: https://codeforces.com/contest/2154/submission/399712347

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 1e18;
void solve() {
    int n; cin >> n;
    vector<ll> v(n, 0);
    for(int i = 0; i < n; i++) cin >> v[i];
    ll p_max = 0;
    for(int i = 0; i < n; i++) {
        p_max = max(p_max, v[i]);
        if(i & 1) v[i] = p_max;
    }
    ll op = 0;
    for(int i = 0; i < n; i += 2) {
        op += max(0LL, v[i] + 1 - min(i == 0 ? INF : v[i-1], i == n-1 ? INF : v[i+1])); 
    }
    cout << op << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; cin >> t; while(t--) solve();
}
