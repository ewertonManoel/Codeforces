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

void solve(int n, int k) {
    vector<int> ans(n, 0); for(int i = 0; i < n; i++) ans[i] = i;
    cout << "YES" << '\n';
    k ^= n;
    if(k == 0) swap(ans[0], ans[n-1]);
    else if(k <= n - 1) {
        swap(ans[k], ans[n-1]);
        swap(ans[0], ans[n-2]);
    }
    else {
        int a = n - 1;
        int b = k ^ a;
        if(a > b) swap(a, b);
        swap(ans[a], ans[n-2]);
        swap(ans[b], ans[n-1]);
        swap(ans[0], ans[n-3]);
    }
    for(int i : ans) cout << i << " ";
    cout << '\n';
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        ll n; ll k; cin >> n >> k;
        if (n == 1) {
            if(k == 1) solve(n, k);
            else cout << "NO" << '\n';
        }
        else {
            int K = k ^ n;
            int n_MST = 63 - __builtin_clzll(n-1);
            if(K >= 2 * (1LL << n_MST) || (K < n && (n == (1LL << n_MST)))) cout << "NO" << '\n';
            else solve(n, k);
        }
    }
}