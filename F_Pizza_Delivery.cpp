#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

vector<vector<ll>> memo;
vector<vector<pll>> new_coordinates;
ll ax, ay, bx, by;

ll dist(ll px, ll py, ll qx, ll qy) {return abs(px - qx) + abs(py - qy);}

ll dp(int n, bool pos) {
    if(n == 0) return 0;
    if(memo[n][pos] != -1) return memo[n][pos];
    ll x = new_coordinates[pos][n].first, y = new_coordinates[pos][n].second;
    ll x2 = new_coordinates[!pos][n].first, y2 = new_coordinates[!pos][n].second;
    ll x3 = new_coordinates[0][n-1].first, y3 = new_coordinates[0][n-1].second;
    ll x4 = new_coordinates[1][n-1].first, y4 = new_coordinates[1][n-1].second;
    return memo[n][pos] = dist(x, y, x2, y2) + min(dist(x2, y2, x3, y3) + dp(n-1, 0), dist(x2, y2, x4, y4) + dp(n-1, 1));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n >> ax >> ay >> bx >> by;
        vector<ll> vect(n, 0);
        vector<pll> coordinates;
        for(int i = 0; i < n; i++) cin >> vect[i];
        for(int i = 0; i < n; i++) {
            ll y; cin >> y;
            coordinates.pb({vect[i], y});
        }
        if(n == 1) {
            ll ans = dist(ax, ay, coordinates[0].first, coordinates[0].second) + dist(coordinates[0].first, coordinates[0].second, bx, by);
            cout << ans << '\n';
            continue;
        }
        sort(all(coordinates));
        ll minimum = coordinates[0].second;
        ll maximum = coordinates[0].second;
        new_coordinates.assign(2, vector<pll>());
        new_coordinates[0].pb({ax, ay});
        new_coordinates[1].pb({ax, ay});
        for(int i = 1; i < n; i++) {
            if(coordinates[i-1].first != coordinates[i].first) {
                new_coordinates[0].pb({coordinates[i-1].first, minimum});
                new_coordinates[1].pb({coordinates[i-1].first, maximum});
                minimum = LINF;
                maximum = -LINF;
            }
            minimum = min(minimum, coordinates[i].second);
            maximum = max(maximum, coordinates[i].second);
            if(i == n-1) {
                new_coordinates[0].pb({coordinates[i].first, minimum});
                new_coordinates[1].pb({coordinates[i].first, maximum});
            }
        }
        int last = new_coordinates[0].size() - 1;
        ll x = new_coordinates[0][last].first;
        ll y = new_coordinates[0][last].second;
        ll x2 = new_coordinates[1][last].first;
        ll y2 = new_coordinates[1][last].second;
        memo.assign(last + 1, vector<ll>(2, -1));
        ll ans = min(dp(last, 0) + dist(bx, by, x, y), dp(last, 1) + dist(bx, by, x2, y2));
        cout << ans << '\n';
    }
}