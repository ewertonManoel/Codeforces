// Problem: 1862E - Kolya and Movie Theatre
// Contest: 1862 | Rating: 1600 | Tags: constructive algorithms, data structures, greedy
// Language: C++20 (GCC 13-64) | Time: 78 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/1862/problem/E
// Submission: https://codeforces.com/contest/1862/submission/399845649

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, k; ll d; cin >> n >> k >> d;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    ll total_sum = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        ll x; cin >> x;
        if(x <= 0) continue;
        pq.push(x);
        total_sum += x;
        if(pq.size() > k) {
            total_sum -= pq.top();
            pq.pop();
        }
        ans = max(ans, total_sum - i * d);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t; while(t--) solve();
}
