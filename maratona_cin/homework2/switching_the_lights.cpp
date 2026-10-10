#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    ll n; int m, q; cin >> n >> m >> q;
    vector<ll> coordinates(m, 0);
    for(int i = 0; i < m; i++) cin >> coordinates[i];
    vector<ll> indexes = coordinates;
    sort(indexes.begin(), indexes.end());
    indexes.erase(unique(indexes.begin(), indexes.end()), indexes.end());
    vector<int> lights(m, 0);
    for(int i = 0; i < q; i++) {
        ll l_val, r_val; cin >> l_val >> r_val;
        int l = lower_bound(indexes.begin(), indexes.end(), l_val) - indexes.begin();
        int r = upper_bound(indexes.begin(), indexes.end(), r_val) - indexes.begin() - 1;
        if(l <= r) {
            if(l < m) lights[l] ^= 1;
            if(r + 1 < m) lights[r + 1] ^= 1;
        }
    }
    for(int i = 0; i < m - 1; i++) lights[i+1] ^= lights[i];
    int ans = count(lights.begin(), lights.end(), 1);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}