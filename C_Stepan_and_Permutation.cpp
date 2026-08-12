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

int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}
int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n, x, y; cin >> n >> x >> y; 
        int z = gcd(x, y);
        bool result = true;
        for(int i = 0; i < n; i++) {
            int j; cin >> j; j--; int d = abs(i - j);
            if(d % z) result = false; 
        }
        if(result) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}