#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const ll INF = 1e18;

bool compare(pll a, pll b) {
    if(a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

vector<pll> pruning(vector<pll>& items) {
    vector<pll> good_items;
    int n = items.size();
    sort(items.begin(), items.end(), compare);
    ll biggest = 0;
    for(int i = 0; i < n; i++) {
        if(items[i].second > biggest) {
            biggest = items[i].second;
            good_items.push_back(items[i]);
        }
    }
    return good_items;
}

void solve() {
    int n, cap; cin >> n >> cap;
    vector<pll> items(n);
    for(int i = 0; i < n; i++) {
        string s; ll v; cin >> s >> v;
        items[i] = {(ll)s.size(), v};
    }
    vector<pll> good_items = pruning(items);
    n = good_items.size();
    ll dp[cap + 1]; memset(dp, 0, sizeof(dp));
    for(int i = 0; i <= cap; i++) {
        for(int j = 0; j < n; j++) {
            auto [w, v] = good_items[j];
            if(i + w <= cap) dp[i + w] = max(dp[i + w], dp[i] + v);
        }
    }
    cout << dp[cap] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}