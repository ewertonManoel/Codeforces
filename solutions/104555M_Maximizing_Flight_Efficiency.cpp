// Problem: 104555M - Maximizing Flight Efficiency
// Contest: 104555
// Language: C++20 (GCC 13-64) | Time: 62 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/104555/problem/M
// Submission: https://codeforces.com/gym/104555/submission/400113399

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 1e18;

set<pair<int, int>> nodes;
vector<vector<ll>> floyd_warshall(vector<vector<ll>> dist) {
    int n = dist.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(dist[i][k] == INF) continue;
            for(int j = 0; j < n; j++) {
                if(dist[k][j] == INF || k == i || k == j) continue;
                if(dist[i][j] == dist[i][k] + dist[k][j]) nodes.insert({min(i, j), max(i, j)});
                dist[i][j] = min(dist[i][j], max(-INF, dist[i][k] + dist[k][j]));
            }
        }
    }
    return dist;
}

void solve() {
    int n; cin >> n;
    vector<vector<ll>> dist(n, vector<ll>(n, INF));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            ll x; cin >> x;
            dist[i][j] = x;
        }
    }
    vector<vector<ll>> dist_cpy = floyd_warshall(dist);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist_cpy[i][j] < dist[i][j]) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    cout << nodes.size() << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
