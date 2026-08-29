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
        string s1, s2; cin >> s1 >> s2;
        vector<int> pref_u(n+1, 0); vector<int> pref_v(n+1, 0);
        vector<int> pref_x(n+1, 0); vector<int> pref_y(n+1, 0);
        for(int i = 1; i < n + 1; i++) {
            pref_u[i] = pref_u[i-1]; pref_v[i] = pref_v[i-1]; pref_x[i] = pref_x[i-1]; pref_y[i] = pref_y[i-1];
            if(s1[i-1] == '0' && s2[i-1] == '0')  pref_u[i] += 1;
            else if(s1[i-1] == '1' && s2[i-1] == '1')  pref_v[i] += 1;
            else if(s1[i-1] == '1' && s2[i-1] == '0')  pref_x[i] += 1;
            else pref_y[i] += 1;
        }
        for(int i = 0; i < q; i++) {
            int l, r; cin >> l >> r;
            int u, v, x, y;
            u = pref_u[r] - pref_u[l-1];
            v = pref_v[r] - pref_v[l-1];
            x = pref_x[r] - pref_x[l-1];
            y = pref_y[r] - pref_y[l-1];
            if(abs(x - y) <= u + v) cout << "YES" << '\n';
            else cout << "NO" << '\n';
        }
    }
}