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
        string s; cin >> s;
        vector<int> prefixSum(n+1, 0);
        for(int i = 1; i < n; i++) {
            prefixSum[i+1] = prefixSum[i] + (s[i] == s[i-1] ? 1 : 0);
        }
        for(int i = 0; i < q; i++) {
            int l, r, k; cin >> l >> r >> k;
            int badBridges = prefixSum[r] - prefixSum[l];
            if(k < (badBridges + 1) / 2) cout << "NO" << '\n';
            else cout << "YES" << '\n';
        }
    }
}