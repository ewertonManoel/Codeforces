// Problem: 105791D - Darts
// Contest: 105791
// Language: C++20 (GCC 13-64) | Time: 1140 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105791/problem/D
// Submission: https://codeforces.com/gym/105791/submission/399953457

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> fact, inv_fact;

ll modpow(ll a, ll b, ll mod) {
    ll ans = 1 % mod;
    a = (a % mod + mod) % mod;
    
    while(b > 0) {
        if(b & 1) ans = (__int128)ans * a % mod;
        a = (__int128)a * a % mod;
        b >>= 1;
    }
    return ans;
}

tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
    if(b == 0) return {a, 1, 0};
    auto [g, x1, y1] = extended_gcd(b, a % b);
    ll x = y1, y = x1 - (a / b) * y1;
    return {g, x, y};
}

ll mod_inverse(ll a, ll mod) {
    a = (a % mod + mod) % mod;
    auto [g, x, y] = extended_gcd(a, mod);
    if(g != 1) return -1;
    return (x % mod + mod) % mod;
}

void precompute_factorials(ll n, ll mod) {
    fact.resize(n + 1);
    inv_fact.resize(n + 1);
    fact[0] = 1;
    
    for(ll i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    inv_fact[n] = mod_inverse(fact[n], mod);
    for(ll i = n; i >= 1; i--) {
        inv_fact[i - 1] = (inv_fact[i] * i) % mod;
    }
}

vector<ll> S;


ll nCr(ll n, ll r, ll mod) {
    if(r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % mod * inv_fact[n - r] % mod;
}

const ll mod = 1e9 + 7;

ll calc1(ll k) {
    return mod_inverse(k + 1, mod);
}

ll calc2(ll n, ll k) {
    return ((((modpow(1 + n, k + 1, mod) - n - 1) % mod) + mod) % mod);
}

ll calc3(ll k) {
    ll ans = 0;
    for(int i = 1; i <= k - 1; i++) {
        ans = (ans + (nCr(k + 1, i, mod) * S[i]) % mod) % mod;
    }
    return ans;
}

void solve() {
    ll n, k; cin >> n >> k;
    S.assign(k + 1, 0);
    //Sk=1k+1((1+n)k+1−n−1−∑i=1k−1(k+1i)Si)
    for(int i = 1; i <= k; i++) {
        S[i] = (calc1(i) * ((((calc2(n, i) - calc3(i)) % mod) + mod) % mod)) % mod;
    }
    cout << S[k] << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    precompute_factorials(1e3 + 10, mod);
    int t = 1; cin >> t; while(t--) solve();
}
