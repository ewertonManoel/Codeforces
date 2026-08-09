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
vector<pii> l;
vector<pii> r;
int n;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        cin >> n;
        l.clear(); r.clear(); l.pb({}); r.pb({});
        for(int i = 0; i < n; i++) {
            int li, ri, ui, vi; cin >> li >> ri >> ui >> vi;
            l.pb({li, ri}); r.pb({ui, vi});
        }
        int ans = 0;
        for(int m = n; m >= 0; m--) {
            int k = n; bool result = true;
            for(int i = 1; i <= n; i++) {
                int j = n - k;
                int li = i - j, ri = m - li + 1;
                if(li >= l[i].first && li <= l[i].second || ri >= r[i].first && ri <= r[i].second) k--;
                if(k < m) {
                    result = false;
                    break;
                }
            }
            if(result) {
                ans = m;
                break;
            }
        }
        cout << ans << '\n';        
    }
}