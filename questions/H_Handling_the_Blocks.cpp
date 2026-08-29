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
vector<pii> original;
vector<pii> sorted;
int main() {
    fast_io();
    int n; cin >> n;
    int k; cin >> k;
    for(int i = 0; i < n; i++) {
        int ni; cin >> ni;
        int ci; cin >> ci;
        original.pb({ni, ci});
    }
    sorted = original;
    sort(all(sorted));
    bool same = true;
    for(int i = 0; i < n; i++) {
        if(original[i].second != sorted[i].second) {
            same = false;
            break;
        }
    }
    if(same) cout << 'Y' << '\n';
    else cout << 'N' << '\n';
}