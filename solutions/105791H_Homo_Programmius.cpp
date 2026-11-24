// Problem: 105791H - Homo Programmius
// Contest: 105791
// Language: C++20 (GCC 13-64) | Time: 140 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105791/problem/H
// Submission: https://codeforces.com/gym/105791/submission/399652787

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int mod = 1e9 + 7;

struct Fenwick {
    vector<ll> bit;
    Fenwick(int n = 0) : bit(n + 1) {}
    void add(int i, ll v) {for(; i < bit.size(); i |= i + 1) bit[i] += v;}
    ll query(int i) {ll s = 0; for(; i >= 0; i = (i & (i + 1)) - 1) s += bit[i]; return s;}
};

Fenwick f;

bool check(int mid, int pos) {return (f.query(pos) - f.query(mid) == 0);}

int bs_left(int l, int r) {
    int idx = r;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid, idx)) r = mid - 1;
        else l = mid + 1;
    }
    return l;
}

int bs_right(int l, int r) {
    int idx = l;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(check(mid, idx - 1)) l = mid + 1;
        else r = mid - 1;
    }
    return l;
}

ll calculate(ll x) {return (x * (x + 1) / 2);}

void solve() {
    int n; cin >> n;
    string s; cin >> s; s = " " + s;
    f = Fenwick(n);
    int prev = 1;
    ll ans = calculate(n);
    int count = 0;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') count++;
        if(s[i] == '1' || i == n) {
            ans -= calculate(count);
            count = 0;
        }
        f.add(i, s[i] - '0');
    } 
    int m; cin >> m;
    while(m--) {
        int pos; char val; cin >> pos >> val;
        if(s[pos] != val) {
            int change = (val - '0') - (s[pos] - '0');
            int l = bs_left(0, pos - 1), r = bs_right(pos + 1, n);
            ans += change * calculate(r - l - 1);
            ans -= change * ((calculate(pos - l - 1)) + calculate(r - pos - 1)); 
            f.add(pos, change);
            s[pos] = val;
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
