#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back
#define ff first
#define ss second

const int INF = 1e8 + 7;

int h[4] = {-1, 1, 0, 0};
int v[4] = {0, 0, -1, 1};

void solve() {
    int n, m; cin >> n >> m;
    pii st; cin >> st.ff >> st.ss; st.ff--; st.ss--;
    pii end; cin >> end.ff >> end.ss; end.ff--; end.ss--;
    vector<vector<int>> grid(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> grid[i][j];
    int ans = 10;
    for(int mask = 0; mask < (1 << 10); mask++) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pii> q;
        if((mask >> (grid[st.ff][st.ss] - 1)) & 1) q.push(st);
        bool found = false;
        while(!q.empty()) {
            pii p = q.front(); q.pop();
            if(p == end) found = true;
            auto [r, c] = p;
            for(int i = 0; i < 4; i++) {
                int nr = r + v[i], nc = c + h[i];
                if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                if(visited[nr][nc]) continue;
                if((mask >> (grid[nr][nc] - 1)) & 1) q.push({nr, nc});
                visited[nr][nc] = true;
            }
        }
        if(found) {
            ans = min(ans, __builtin_popcount(mask));
        }
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 
