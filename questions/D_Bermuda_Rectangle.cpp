#include <bits/stdc++.h>

#define pb push_back
#define ff first
#define ss second

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<int> primes;
vector<pll> fact, fact2;

void sieve() {
    int n = 1e7+5;
    vector<bool> p(n, true);
    for(int i = 2; i * i < n; i++) {
        if(!p[i]) continue;
        for(int j = i * i; j < n; j += i) p[j] = false;
    }
    for(int i = 2; i < n; i++) if(p[i]) primes.pb(i);
}

void factoration(ll s) {
    vector<ll> divisors; divisors.pb(1);
    ll x = s; int sz;
    for(int i : primes) {
        if((ll)i * i > x) break;
        ll j = 1, sz = divisors.size();
        while(x % i == 0) {
            x /= i; j *= i;
            for(int i = 0; i < sz; i++) divisors.pb(divisors[i] * j);
        }
    }
    sz = divisors.size();
    if(x > 1) for(int i = 0; i < sz; i++) divisors.pb(divisors[i] * x);
    for(ll val : divisors) fact.pb({val, s/val});
}

bool cmp(ll x, pll p) {return x < p.first;}
bool cmp2(pll p, ll x) {return p.first < x;}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    sieve();
    while(t--) {
        fact.clear();
        ll s; int q; cin >> s >> q;
        factoration(s); int n = fact.size();
        sort(fact.begin(), fact.end());
        vector<ll> pre_col(n+1, 0);
        for(int i = 0; i < n; i++) pre_col[i+1] = pre_col[i] + (fact[i].ff - (i-1 < 0 ? 0 : fact[i-1].ff)) * fact[i].ss;
        while(q--) {
            ll ans = 0, x, y; cin >> x >> y;
            x = min(x, fact.back().ff); y = min(y, fact[0].ss);
            int idx_x = (upper_bound(fact.begin(), fact.end(), s / y, cmp) - fact.begin());
            int idx_x2 = (lower_bound(fact.begin(), fact.end(), x, cmp2) - fact.begin());
            if(idx_x2 < idx_x) ans = x * y;
            else {
                ll slice1 = (idx_x == 0 ? 0 : fact[idx_x-1].ff) * y;
                ll slice2 = pre_col[idx_x2] - pre_col[idx_x];
                ll slice3 = (x - fact[idx_x2-1].ff) * (fact[idx_x2].ss);
                ans = slice1 + slice2 + slice3;
            }
            cout << ans << '\n';
        }
    }
}