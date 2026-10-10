#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
void solve() {
    int n; cin >> n;
    vector<ll> coordinates;
    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        coordinates.push_back(a);
        coordinates.push_back(b);
    }
    vector<ll> indexes = coordinates;
    sort(indexes.begin(), indexes.end());
    indexes.erase(unique(indexes.begin(), indexes.end()), indexes.end());
    int m = coordinates.size();
    for(int i = 0; i < m; i++) {
        coordinates[i] = lower_bound(indexes.begin(), indexes.end(), coordinates[i]) - indexes.begin();
    }
    vector<ll> psum(m, 0);
    for(int i = 0; i < m; i++) {
        if(i % 2 == 0) psum[coordinates[i]]++;
        else psum[coordinates[i]]--;
    }
    for(int i = 0; i < m - 1; i++) psum[i + 1] += psum[i];
    ll maximum = *max_element(psum.begin(), psum.end());
    cout << maximum << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}