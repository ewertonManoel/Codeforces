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
        int n; cin >> n;
        vector<int> prefix1(n + 1, 0);
        vector<int> prefix2(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            if(x == 1) {
                prefix1[i] = prefix1[i-1] + 1; 
                prefix2[i] = prefix2[i-1] + 1;
            }
            else if(x == 2) {
                prefix1[i] = prefix1[i-1] - 1;
                prefix2[i] = prefix2[i-1] + 1;
            }
            else {
                prefix1[i] = prefix1[i-1] - 1; 
                prefix2[i] = prefix2[i-1] - 1;
            }
        }
        int minPrefix = INF;
        bool yes = false;
        for(int i = 1; i < n; i++) {
            if(prefix2[i] >= minPrefix) {
                yes = true;
                break;
            }
            if(prefix1[i] >= 0) minPrefix = min(minPrefix, prefix2[i]);
        }
        if(yes) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}