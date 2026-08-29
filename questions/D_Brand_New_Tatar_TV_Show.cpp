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
map<int, int> mp;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        mp.clear();
        int n; cin >> n;
        int k; cin >> k;
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            mp[x]++;
        }
        string ans = "NO";
        for(auto it = mp.rbegin(); it != mp.rend(); it++) {
            int value = it->first;
            int frequency = it->second;
            if(frequency % 2 == 0) {
                ans = "YES";
                break;
            }
            if(next(it) != mp.rend()) {
                int next_value = next(it)->first;
                if(value - next_value <= k) {
                    ans = "YES";
                    break;
                }
            }
        }
        cout << ans << '\n';
    }
}