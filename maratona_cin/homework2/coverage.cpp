#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> vect(m, 0);
    for(int i = 0; i < m; i++) {
        int c; cin >> c;
        int mask = 0;
        for(int j = 0; j < c; j++) {
            int x; cin >> x;
            mask |= (1 << (x - 1));
        }
        vect[i] = mask;
    }
    ll count = 0;
    for(int mask = 0; mask < (1 << m); mask++) {
        int set_mask = 0;
        for(int bit = 0; bit < m; bit++) {
            if((mask >> bit) & 1) set_mask |= vect[(m - (bit + 1))];
        }
        if(set_mask == (1 << n) - 1) count++;
    }
    cout << count << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}