#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;

const ll INF = 1e18;
const int MAX = 5e7;

void solve() {
    int n; ll cap; cin >> n >> cap;
    vector<pll> items(n);
    for(int i = 0; i < n; i++) cin >> items[i].first >> items[i].second;
    if(cap * n < MAX) {
        ll dp[cap + 1]; memset(dp, 0, sizeof(dp));
        for(int i = 0; i <= cap; i++) {
            for(int j = 0; j < n; j++) {
                auto [w, v] = items[j];
                if(i + w <= cap) dp[i + w] = max(dp[i + w], dp[i] + v);
            }
        }
        cout << dp[cap] << '\n';
        return;
    }
    ll winner_w = 1, winner_v = 0;
    for(auto [w, v] : items) {
        if((double) v / w > (double) winner_v / winner_w) {
            winner_v = v;
            winner_w = w;
        }
    }
    int MOD = winner_w;
    vector<vector<tuple<int, ll, ll, ll>>> adj(MOD);
    for(int i = 0; i < MOD; i++) {
        for(int j = 0; j < n; j++) {
            auto [w, v] = items[j];
            adj[i].pb({(i + w) % MOD, w * winner_v - winner_w * v, w, v});
        }
    }
    vector<ll> dist(MOD, INF);
    vector<ll> value(MOD, 0);
    vector<ll> weight(MOD, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, d, w, c] : adj[u]) {
            if (dist[u] + d < dist[v] && weight[u] + w <= cap) {
                dist[v] = dist[u] + d;
                weight[v] = weight[u] + w;
                value[v] = value[u] + c;
                pq.push({dist[v], v});
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < MOD; i++) {
        if(weight[i] <= cap) {
            ans = max(ans, value[i] + ((cap - weight[i]) / winner_w) * winner_v);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}