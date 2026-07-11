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
        bool yep = false;
        while(n--) {
            int x; cin >> x;
            if(x == 67) yep = true;
        }
        if(yep) cout << "yes" << '\n';
        else cout << "no" << '\n';
    }
}