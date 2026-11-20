// Problem: 102890G - Gold Fever
// Contest: 102890
// Language: C++20 (GCC 13-64) | Time: 93 ms | Memory: 500 KB
// Problem Link: https://codeforces.com/gym/102890/problem/G
// Submission: https://codeforces.com/gym/102890/submission/399259649

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SegTree {
    const ll NEUTRAL = 0;
    int n; vector<ll> st;
    SegTree(int n) : n(n), st(4 * n, NEUTRAL) {}
    SegTree(vector<ll>& a) : SegTree(a.size()) {build(a, 1, 0, n - 1);}

    ll merge(ll a, ll b) { return max(a, b); }

    void build(vector<ll>& a, int p, int l, int r) {
        if (l == r) { st[p] = a[l]; return; }
        int m = l + (r - l) / 2;
        build(a, p * 2, l, m); build(a, p * 2 + 1, m + 1, r);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    void update(int idx, ll val, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) { st[p] = val; return; }
        int m = l + (r - l) / 2;
        idx <= m ? update(idx, val, p * 2, l, m) : update(idx, val, p * 2 + 1, m + 1, r);
        st[p] = merge(st[p * 2], st[p * 2 + 1]);
    }

    ll query(int ql, int qr, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (r < ql || l > qr) return NEUTRAL;
        if (ql <= l && r <= qr) return st[p];
        int m = l + (r - l) / 2;
        return merge(query(ql, qr, p * 2, l, m), query(ql, qr, p * 2 + 1, m + 1, r));
    }
};

void solve() {
    int n; cin >> n; 
    SegTree seg(n);

    vector<tuple<int, int, int>> v(n);
    for(int i = 0; i < n; i++) {
        int g, a, b; cin >> g >> a >> b;
        v[i] = {g, a, b};
    }
    for(int i = n-1; i >= 0; i--) {
        auto [g, a, b] = v[i];
        seg.update(i, g + seg.query(i + a, i + b));
    }
    cout << seg.query(0, n-1) << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
