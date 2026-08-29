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
        int maximum = -INF;
        int minimum = INF;
        while(n--) {
            int h; cin >> h;
            maximum = max(maximum, h);
            minimum = min(minimum, h);
        }
        int ans = (maximum + 1) - minimum;
        cout << ans << '\n';
    }
}