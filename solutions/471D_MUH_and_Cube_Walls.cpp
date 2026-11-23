// Problem: 471D - MUH and Cube Walls
// Contest: 471 | Rating: 1800 | Tags: string suffix structures, strings
// Language: C++20 (GCC 13-64) | Time: 93 ms | Memory: 15000 KB
// Problem Link: https://codeforces.com/contest/471/problem/D
// Submission: https://codeforces.com/contest/471/submission/399611178

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M1 = 1e9 + 7, M2 = 1e9 + 9;
const ll B = uniform_int_distribution<ll>(256, M1 - 1)(rng);

struct StringHash {
    int n;
    vector<ll> h1, h2, p1, p2;

    StringHash(const vector<ll>& s = {}) : n(s.size()) {
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        for(int i = 0; i < n; i++) {
            p1[i + 1] = p1[i] * B % M1;
            p2[i + 1] = p2[i] * B % M2;
            h1[i + 1] = (h1[i] * B + s[i]) % M1;
            h2[i + 1] = (h2[i] * B + s[i]) % M2;
        }
    }

    pll query(int l, int r) {
        ll x1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % M1 + M1) % M1;
        ll x2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % M2 + M2) % M2;
        return {x1, x2};
    }
};

ll mod_cmp1(ll a, ll b) {return (((a % M1) + M1) % M1) == (((b % M1) + M1) % M1);} 
ll mod_cmp2(ll a, ll b) {return (((a % M2) + M2) % M2) == (((b % M2) + M2) % M2);} 

void solve() {
    int n, w; cin >> n >> w;
    vector<ll> s1, s2, base;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        s1.push_back(x);
    }
    for(int i = 0; i < w; i++) {
        int x; cin >> x;
        s2.push_back(x);
        base.push_back(1);
    }
    StringHash hash_s1(s1), hash_s2(s2), hash_base(base);
    auto [v2_f, v2_s] = hash_s2.query(0, w-1);
    auto [vb_f, vb_s] = hash_base.query(0, w-1);
    int cnt = 0;
    for(int i = 0; i <= n - w; i++) {
        ll diff = s1[i] - s2[0];
        auto [v1_f, v1_s] = hash_s1.query(i, i + w - 1);
        if(mod_cmp1(v1_f - v2_f, diff * vb_f) && mod_cmp2(v1_s - v2_s, diff * vb_s)) cnt++;
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
