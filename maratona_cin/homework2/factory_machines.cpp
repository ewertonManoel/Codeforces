#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
vector<ll> machines;

ll calculate_products(ll time) {
    ll count = 0;
    for(ll val : machines) count += (time / val);
    return count;
}

void solve() {
    int n; ll products; cin >> n >> products;
    machines.assign(n, 0);
    for(int i = 0; i < n; i++) cin >> machines[i];
    ll minimum = *min_element(machines.begin(), machines.end());
    ll l = 0, r = products * minimum;
    while(l < r) {
        ll mid = l + (r - l) / 2;
        if(calculate_products(mid) >= products) r = mid;
        else l = mid + 1;
    }
    cout << r << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}