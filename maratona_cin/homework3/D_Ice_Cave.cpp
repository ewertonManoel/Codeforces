#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

int v[4] = {0, 0, -1, 1};
int h[4] = {-1, 1, 0, 0};
int n, m, ri, ci, rf, cf;
vector<string> adj;

bool search(int r, int c) {
    if(r < 0 || r >= n || c < 0 || c >= m) return false;
    if(r == rf && c == cf) return true;
    adj[r][c] = 'X';
    for(int i = 0; i < 4; i++) {
        int nr = r + v[i], nc = c + h[i];
        if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        if(adj[nr][nc] != 'X') {
            if(search(nr, nc)) return true;
        }
    }
    return false;
}

void solve() {
    cin >> n >> m;
    adj.resize(n);
    for(int i = 0; i < n; i++) cin >> adj[i];
    cin >> ri >> ci >> rf >> cf; ri--; ci--; rf--; cf--;
    bool ok = false;
    if(adj[rf][cf] == 'X' && (ri != rf || ci != cf)) ok = true;
    else {
        int count = 0;
        for(int i = 0; i < 4; i++) {
            int nr = rf + v[i], nc = cf + h[i];
            if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if(adj[nr][nc] == '.' || (nr == ri && nc == ci)) count++;
        }
        if(ri == rf && ci == cf) {
            if(count >= 1) ok = true;
        }
        else if(count >= 2) ok = true;
    }
    if(adj[rf][cf] == 'X') adj[rf][cf] = '#';
    if(ok) ok = search(ri, ci);
    if(ok) cout << "YES" << '\n';
    else cout << "NO" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 