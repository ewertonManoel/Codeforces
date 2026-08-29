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
const ll MAX_INPUT = 500005;
ll spf[MAX_INPUT];

void sieve() {
    for(ll i = 0; i < MAX_INPUT; i++) {
        spf[i] = i;
    }
    for(ll i = 2; i < MAX_INPUT; i++) {
        if(spf[i] == i) {
            for(ll j = i * i; j < MAX_INPUT; j += i) {
                if(spf[j] == j) spf[j] = i;
            }
        }
    }
}
int main() {
    fast_io();
    sieve();
    int t; cin >> t;
    while(t--) {
        unordered_map<int, int> mp;
        int n; cin >> n;
        int x; cin >> x;
        for(int i = 0; i < n; i++) {
            int val; cin >> val;
            while(val != 1) {
                mp[spf[val]]++;
                val /= spf[val];
            } 
        }
        ll ans = 1;
        for(const auto& [key, value] : mp) ans = (ans * ((value + 1) % MOD)) % MOD;
        cout << ans << '\n';
    }
}