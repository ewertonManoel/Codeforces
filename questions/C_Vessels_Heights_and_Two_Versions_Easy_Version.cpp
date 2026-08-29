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
const double EPS = 1e-9;
int n, MOD; vector<ll> h, w;

int mod(int a, int b) {return ((a % b) + b) % b;}

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        cin >> n; h.assign(n, 0); w.assign(n, 0); MOD = n;
        for(int i = 0; i < n; i++) cin >> h[i];
        for(int i = 0; i < n; i++) {
            fill(all(w), 0);
            int r = (i+1) % MOD;
            int l = mod(i-1, MOD);
            w[r] = h[i]; w[l] = h[l];
            while(true) {
                if(w[r] < w[l]) {
                    int rr = (r+1) % MOD;
                    if(rr == l) {
                        w[l] = min(w[l], max(w[r], h[r]));
                        break;
                    }
                    if(w[rr] == 0) w[rr] = max(w[r], h[r]);
                    r = rr;
                }
                else {
                    int ll = mod(l-1, MOD);
                    if(ll == r) {
                        w[r] = min(w[r], max(w[l], h[ll]));
                        break;
                    }
                    if(w[ll] == 0) w[ll] = max(w[l], h[ll]);
                    l = ll;
                }
            }
            ll total_sum = accumulate(all(w), 0LL);
            cout << total_sum << " ";
        }
        cout << '\n';
    }
}