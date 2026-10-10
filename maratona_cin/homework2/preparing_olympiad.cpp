#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n; ll l, r, x; cin >> n >> l >> r >> x;
    vector<ll> v(n, 0);
    for(int i = 0; i < n; i++) cin >> v[i];
    ll p = 0;
    for(int mask = 0; mask < (1 << n); mask++) {
        ll sum = 0, minimum = LLONG_MAX, maximum = LLONG_MIN; int count = 0;
        for(int bit = 0; bit < n; bit++) {
            if((mask >> bit) & 1) {
                int idx = n - (bit + 1);
                sum += v[idx];
                maximum = max(maximum, v[idx]);
                minimum = min(minimum, v[idx]);
                count++;
            }
        }
        if(count >= 2 && sum >= l && sum <= r && maximum - minimum >= x) {
            p++;
        }
    }
    cout << p << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}