// Problem: 105791M - Mayor
// Contest: 105791
// Language: C++20 (GCC 13-64) | Time: 62 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105791/problem/M
// Submission: https://codeforces.com/gym/105791/submission/399954551

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<vector<ll>> costs(n, vector<ll>(n, 0));
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> costs[i][j];
    vector<ll> permutation(n-1); iota(permutation.begin(), permutation.end(), 1);
    ll ans = -1;
    if(n == 1) {
        cout << 0 << '\n';
        return;
    }
    do {
        ll c = costs[0][permutation.front()] + costs[permutation.back()][0];
        for(int i = 0; i < n-2; i++) c += costs[permutation[i]][permutation[i+1]];
        if(ans == -1 || c < ans) {
            ans = c;
        }
    } while(next_permutation(permutation.begin(), permutation.end()));
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
