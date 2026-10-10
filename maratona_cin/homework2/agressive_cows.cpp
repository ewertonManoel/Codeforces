#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool check(vector<ll>& stalls, ll dist, int c) {
    ll prev_val = stalls[0];
    int cows = 0;
    for(ll val : stalls) {
        if(val - prev_val >= dist) {
            cows++;
            prev_val = val;
        }
    }
    return cows + 1 >= c;
}

void solve() {
    int n, c; cin >> n >> c;
    vector<ll> stalls(n, 0);
    for(int i = 0; i < n; i++) cin >> stalls[i];
    sort(stalls.begin(), stalls.end());
    ll l = 0, r = LLONG_MAX;
    while(l <= r) {
        ll mid = l + (r - l) / 2;
        if(check(stalls, mid, c)) l = mid + 1;
        else r = mid - 1;
    }
    cout << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; cin >> t; while(t--) solve();
}