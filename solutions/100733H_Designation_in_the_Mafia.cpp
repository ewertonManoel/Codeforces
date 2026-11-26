// Problem: 100733H - Designation in the Mafia
// Contest: 100733
// Language: C++20 (GCC 13-64) | Time: 46 ms | Memory: 300 KB
// Problem Link: https://codeforces.com/gym/100733/problem/H
// Submission: https://codeforces.com/gym/100733/submission/399845637

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void floyd_warshall(vector<vector<ll>>& dist) {
    int n = dist.size();
    const ll INF = 1e18;

    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(dist[i][k] == INF) continue;

            for(int j = 0; j < n; j++) {
                if(dist[k][j] == INF) continue;

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

void solve() {
    vector<vector<ll>> dist(26, vector<ll>(26, 0));
    for(int i = 0; i < 26; i++) {
        for(int j = 0; j < 26; j++) {
            cin >> dist[i][j];
        }
    }
    floyd_warshall(dist);
    string s; cin >> s;
    int n = s.size();

    int l = 0, r = n - 1;
    ll total = 0;
    while(l < r) {
        int a = s[l] - 'a', b = s[r] - 'a';
        l++;
        r--;
        if(a == b) continue;
        ll c = min(dist[a][b], dist[b][a]);
        for(int i = 0; i < 26; i++) {
            c = min(c, dist[a][i] + dist[b][i]);
        }
        total += c;
    }
    cout << total << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}
