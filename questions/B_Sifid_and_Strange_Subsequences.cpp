#include <bits/stdc++.h>

using namespace std;

using ll = long long;

#define LINF 1e18
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> v(n, 0);
        for(int i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(), v.end());
        ll minimum = LINF;
        ll prev = 0;
        int ans = 0;
        for(ll MAX : v) {
            if(ans > 0) minimum = min(minimum, abs(MAX - prev));
            prev = MAX;
            if(minimum >= MAX) ans++;
            else break;
        }
        cout << ans << '\n';
    }
}