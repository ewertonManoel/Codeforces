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
        vector<int> vect;
        vector<vector<bool>> good(n, vector<bool>(n, false));
        int l = 0, r = 0;
        for(int i = 0; i < n; i++) {
            int x; cin >> x; --x;
            vect.pb(x);   
        }
        for(int l = 0; l < n; l++) {
            vector<bool> visited(n, false);
            int maximum = -INF, minimum = INF;
            for(int r = l; r < n; r++) {
                int x = vect[r];
                if(visited[x]) break;
                maximum = max(maximum, x);
                minimum = min(minimum, x);
                if(maximum - minimum == r - l) good[minimum][maximum] = true;
                visited[x] = true;
            }
        }
        bool found = false;
        int k = n / 2;
        for(; k > 0; k--) {
            for(int i = 0; i <= n - 2 * k; i++) {
                if(good[i][i + k - 1] && good[i + k][i + 2 * k - 1]) {
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
        if(!found) k = 0;
        cout << k << '\n';
    }
}