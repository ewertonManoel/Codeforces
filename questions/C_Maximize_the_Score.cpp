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

vector<ll> memo; 
vector<int> vect, first_ocurrence;
ll dp(int r) {
    if(r < 0) return 0;
    if(memo[r] != -1) return memo[r];
    int l = first_ocurrence[vect[r]];
    return memo[r] = max(1 + dp(r-1), (ll)(r-l+1) * (ll)(r-l+1) + dp(l-1));
}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        memo.assign(2 * n, -1); vect.assign(2 * n, -1); first_ocurrence.assign(n, -1);
        for(int i = 0; i < 2*n; i++) {
            int a; cin >> a; a--;
            vect[i] = a;
        }
        for(int i = 2*n-1; i >= 0; i--) first_ocurrence[vect[i]] = i;
        cout << dp(2 * n - 1) << '\n';
    }
}