// Problem: 2263A - Min Max Game
// Contest: 2263 | Rating: 800 | Tags: games
// Language: C++20 (GCC 13-64) | Time: 15 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/2263/problem/A
// Submission: https://codeforces.com/contest/2263/submission/399254819

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, cnt = 0; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        cnt += x;
    }
    if(cnt >= n - cnt) cout << "Bessie\n";
    else cout << "Elsie\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; cin >> t; while(t--) solve();
}
