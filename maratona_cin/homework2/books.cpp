#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n; ll t; cin >> n >> t;
    vector<ll> books(n, 0);
    for(int i = 0; i < n; i++) cin >> books[i];
    int l = 0, sz = 0; ll sum = 0;
    for(int r = 0; r < n; r++) {
        sum += books[r];
        while(sum > t) {
            sum -= books[l];
            l++;
        }
        sz = max(sz, r - l + 1);
    }
    cout << sz << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}