#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int cap = 1e5;
const ll INF = 1e18;

ll dp[cap + 1];

void solve() {
    int n, q; cin >> n >> q;
    vector<ll> items(n + 1);
    for(int i = 0; i <= cap; i++) dp[i] = INF;
    for(int i = 1; i <= n; i++) cin >> items[i];
    for(int i = 1; i <= n; i++) dp[i] = items[i];
    for(int i = 1; i <= cap; i++) {
        for(int j = 1; j <= n; j++) {
            ll w = j, v = items[j];
            if(i + w <= cap && i + w > n) dp[i + w] = min(dp[i + w], dp[i] + v);
        }
    }
    ll weight = 1, winner = items[1];
    for(int i = 1; i <= n; i++) {
        if(items[i] * weight < winner * i) {
            winner = items[i];
            weight = i;
        }
    }
    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        if(k <= cap) cout << dp[k] << '\n';
        else {
            ll num = (k - cap + weight - 1) / weight;
            cout << num * winner + dp[k - num * weight] << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}