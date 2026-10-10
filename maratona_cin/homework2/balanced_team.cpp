#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<ll> v(n, 0);
    for(int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    int count = 0, l = 0;
    for(int r = 0; r < n; r++) {
        while(v[r] > v[l] + 5) l++;
        count = max(count, r - l + 1);
    }
    cout << count << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}