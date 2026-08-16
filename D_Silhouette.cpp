#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;
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
        vector<pli> b;
        bool result = false;
        for(int i = 0; i < n; i++) {
            ll x; cin >> x;
            if(x == 0) result = true;
            b.pb({x, i});
        }
        sort(all(b));
        vector<ll> a(n, 0);
        int prev = 0;
        int count = 1;
        ll value = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++) {
            if(i == n-1) for(int j = prev; j <= i; j++) a[b[j].second] = value + 1;
            else if(b[i+1].first != b[prev].first) {
                ll num = b[i+1].first - sum;
                ll cur = num / count;
                if(num % count != 0 || cur <= value) {
                    result = false;
                    break;
                }
                value = cur;
                for(int j = prev; j <= i; j++) a[b[j].second] = value;
                sum += value * count;
                prev = i+1;
                count = 1;
            }
            else count++;
            if(!result) break;
        }
        if(result) {
            for(ll val : a) cout << val << " ";
            cout << '\n';
        }
        else cout << -1 << '\n';
    }
}