#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

void solve() {
    int n, m; cin >> n >> m;
    if(n > m) {
        cout << n-m << '\n';
        return;
    }
    int maximum = m * 2;
    vector<bool> visited(maximum, false);
    queue<pii> q;
    q.push({n, 0});
    while(!q.empty()) {
        int val = q.front().first, idx = q.front().second; q.pop();
        if(visited[val]) continue;
        visited[val] = true;
        if(val == m) {
            cout << idx << '\n';
            break;
        }
        if(val * 2 < maximum) {
            q.push({val * 2, idx + 1});
        }
        if(val - 1 > 0) {
            q.push({val - 1, idx + 1});
        }
    }
    while(!q.empty()) q.pop();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}