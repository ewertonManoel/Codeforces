#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n; ll target; cin >> n >> target;
    vector<pair<ll, int>> v(n);
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        v[i] = {x, i};
    }
    sort(v.begin(), v.end());
    int l = 0, r = n - 1;
    bool found = false;
    while(l < r) {
        ll sum = v[l].first + v[r].first;
        if(sum == target) {
            cout << v[l].second + 1 << " " << v[r].second + 1 << '\n';
            found = true;
            break;
        }
        else if(sum < target) l++;
        else r--;
    }
    if(!found) cout << "IMPOSSIBLE" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}