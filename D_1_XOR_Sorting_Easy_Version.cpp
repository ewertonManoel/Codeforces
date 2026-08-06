#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n, q; cin >> n >> q;
        vector<ll> v(n+1, 0);
        for(int i = 1; i <= n; i++) {
            ll x; cin >> x;
            v[i] = x;
        }
        bool sorted = true;
        for(int i = 2; i <= n; i++) if(v[i] < v[i-1]) sorted = false;
        if(sorted) {
            cout << 0 << '\n';
            continue;
        }  
        ll j = 0;
        while(true) {
            bool result = true;
            ll prev_max = -LINF;
            ll cur_max = -LINF;
            ll cur_min = LINF;
            for(int i = 1; i <= n; i++) {
                cur_max = max(cur_max, v[i]);
                cur_min = min(cur_min, v[i]);
                if(i % (1LL << (j+1)) == 0 || i == n) {
                    if(cur_min < prev_max) {
                        result = false;
                        break;
                    }
                    prev_max = cur_max;
                    cur_max = -LINF;
                    cur_min = LINF;
                }
            }
            if(result) break;
            j++;
        }
        ll k = 1LL << j;
        cout << k << '\n';
    }
}