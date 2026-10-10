#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

void solve() {
    int n; cin >> n;
    vector<int> apples(n, 0);
    for(int i = 0; i < n; i++) {
        cin >> apples[i];
    }
    ll value = accumulate(apples.begin(), apples.end(), 0LL);
    ll best_result = LLONG_MAX;
    for(int mask = 0; mask < (1 << n); mask++) {
        ll current = 0;
        for(int bit = 0; bit < n; bit++) {
            if((mask >> bit) & 1) {
                current += apples[n - (bit + 1)];
            }
        }
        best_result = min(best_result, abs(value - 2 * current));
    }
    cout << best_result << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}