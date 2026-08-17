#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        map<ll, int> b;
        vll a(n, 0);
        for(int i = 0; i < n; i++) {
            ll x; cin >> x;
            b[x]++;
        }
        ll target = 0;
        bool result = true;
        for(int i = 0; i < n; i++) {
            auto it = b.upper_bound(target);
            if(it == b.end()) {
                result = false;
                break;
            }
            a[i] = it->first;
            if(i > 0) a[i] += a[i-1];
            target = -a[i];
            b[it->first]--;
            if(b[it->first] == 0) b.erase(it);
        }
        if(result) {
            for(ll val : a) cout << val << " ";
            cout << '\n';
        }
        else cout << -1 << '\n';
    }
}