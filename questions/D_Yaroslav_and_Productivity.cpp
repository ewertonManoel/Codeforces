#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<ll> prefix_sum(n+1, 0);
        vector<int> posts(m+1, 0);
        for(int i = 1; i <= n; i++) {
            ll x; cin >> x;
            prefix_sum[i] = prefix_sum[i-1] + x;
        }
        for(int i = 1; i <= m; i++) {
            cin >> posts[i];
        }
        sort(all(posts));
        ll total_sum = 0;
        for(int i = 1; i <= m; i++) {
            ll interval = prefix_sum[posts[i]] - prefix_sum[posts[i-1]];
            total_sum += interval >= 0 ? interval : -interval;
        }
        total_sum += prefix_sum[n] - prefix_sum[posts[m]];
        cout << total_sum << '\n';
    }
}