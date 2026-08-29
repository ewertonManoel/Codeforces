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


int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int k; cin >> k;
        string s; cin >> s;
        for(int i = 0; i < n - k; i++) {
            if(s[i] == '1') {
                s[i] = '0';
                s[i + k] = (s[i + k] == '0' ? '1' : '0');
            }
        }
        string ans = "YES";
        for(int val : s) {
            if(val != '0') {
                ans = "NO";
                break;
            }
        }
        cout << ans << '\n';
    }
}