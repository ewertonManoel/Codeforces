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

ll fast_exp(ll a, int n) {
    ll ans = 1;
    while(n > 0) {
        if(n & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        n >>= 1;
    }
    return ans;    
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> v(n, 0);
        for(int i = 0 ; i < n; i++) {
            ll x; cin >> x;
            v[i] = x;
        }
        ll number = -LINF;
        int d = 0;
        int l = 0;
        for(ll i : v) {
            if(i != number) d++;
            if(i == number + 1) l++;
            number = i;
        }
        if(v[0] != -1) l = 0;
        ll value = (fast_exp(2LL, n - d) * (l+1)) % MOD;
        cout << value << '\n';
    }
}