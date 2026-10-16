#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

const int INF = 1e8 + 7;

int v[4] = {0, 0, -1, 1};
int h[4] = {-1, 1, 0, 0};

void solve() {
    int n, m; cin >> n >> m;

    vector<string> adj(n);
    vector<vector<int>> monster_distance(n, vector<int>(m, INF));
    vector<vector<int>> dude_distance(n, vector<int>(m, INF));
    vector<vector<int>> moves(n, vector<int>(m, -1));
    string out;
    for(int i = 0; i < n; i++) cin >> adj[i];
    queue<pii> q;
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(adj[i][j] == 'M') {
            q.push({i, j});
            monster_distance[i][j] = 0;
        }
    }
    while(!q.empty()) {
        auto[r, c] = q.front(); q.pop();
        for(int i = 0; i < 4; i++) {
            int nr = r + v[i], nc = c + h[i];
            if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if(monster_distance[nr][nc] == INF && adj[nr][nc] != '#') {
                monster_distance[nr][nc] = monster_distance[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        if(adj[i][j] == 'A') {
            q.push({i, j});
            dude_distance[i][j] = 0;
        }
    }
    while(!q.empty()) {
        auto[r, c] = q.front(); q.pop();
        for(int i = 0; i < 4; i++) {
            int nr = r + v[i], nc = c + h[i];
            if(nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if(dude_distance[nr][nc] == INF && adj[nr][nc] != '#') {
                if(i % 2 == 0) moves[nr][nc] = i + 1;
                else moves[nr][nc] = i - 1;
                dude_distance[nr][nc] = dude_distance[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    bool found = false;
    int r, c;
    for(int i = 0; i < n; i++) {
        if(found) break;
        if(dude_distance[i][0] < monster_distance[i][0]) {
            found = true;
            r = i; c = 0;
        }
        if(dude_distance[i][m-1] < monster_distance[i][m-1]) {
            found = true;
            r = i; c = m-1;
        }
    }
    for(int j = 0; j < m; j++) {
        if(found) break;
        if(dude_distance[0][j] < monster_distance[0][j]) {
            found = true;
            r = 0; c = j;
        }
        if(dude_distance[n-1][j] < monster_distance[n-1][j]) {
            found = true;
            r = n-1; c = j;
        }
    }
    if(found) {
        cout << "YES" << '\n';
        int count = 0;
        while(moves[r][c] != -1) {
            count++;
            int mv = moves[r][c];
            if(mv == 0) out += 'R';
            else if(mv == 1) out += 'L';
            else if(mv == 2) out += 'D';
            else out += 'U';
            r = r + v[mv]; c = c + h[mv];
        }
        reverse(out.begin(), out.end());
        cout << count << '\n' << out << '\n';
    }
    else cout << "NO" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
} 
