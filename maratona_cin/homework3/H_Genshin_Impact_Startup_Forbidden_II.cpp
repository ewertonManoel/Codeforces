#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

const int INF = 1e8 + 7;
int h[4] = {-1, 1, 0, 0};
int v[4] = {0, 0, -1, 1};

vector<vector<pii>> grid;
vector<pair<vector<pii>, int>> groups;

int clean(int idx, bool color) {
    int value = groups[idx].first.size();
    for(auto [r, c] : groups[idx].first) {
        grid[r][c] = {-1, -1};
        for(int i = 0; i < 4; i++) {
            int nr = r + v[i], nc = c + h[i];
            if(nr < 0 || nr >= 19 || nc < 0 || nc >= 19) continue;
            if(grid[nr][nc].first == -1) continue;
            if(grid[nr][nc].first != color) groups[grid[nr][nc].second].second++;
        }
    }
    return value;
}
void solve() {
    int n; cin >> n;
    grid.assign(19, vector<pii>(19, {-1, -1}));
    groups.assign(n, pair<vector<pii>, int>());
    for(int j = 0; j < n; j++) {
        bool color = j % 2;
        int r, c; cin >> r >> c; r--; c--;
        int id = j;
        grid[r][c] = {color, id};
        vector<pii> gp(1, {r, c});
        groups[id] = {gp, 0};
        vector<int> deleted(2, 0);
        for(int i = 0; i < 4; i++) {
            int nr = r + v[i], nc = c + h[i];
            if(nr < 0 || nr >= 19 || nc < 0 || nc >= 19) continue;
            if(grid[nr][nc].first == -1) groups[id].second++;
            else {
                int id2 = grid[nr][nc].second;
                groups[id2].second--;
                if(grid[nr][nc].first == color) {
                    if(id != id2) {
                        if(groups[id].first.size() < groups[id2].first.size()) {
                            groups[id2].second += groups[id].second;
                            for(auto p : groups[id].first) {
                                groups[id2].first.pb(p);
                                grid[p.first][p.second].second = id2;
                            }
                            id = id2;
                        }
                        else {
                            groups[id].second += groups[id2].second;
                            for(auto p : groups[id2].first) {
                                groups[id].first.pb(p);
                                grid[p.first][p.second].second = id;
                            }
                            id2 = id;
                        }
                    }
                }
                else {
                    if(groups[id2].second == 0) {
                        deleted[!color] += clean(id2, !color);
                    }
                }
            }
        }
        if(groups[id].second == 0) {
            deleted[color] += clean(id, color);
        }
        cout << deleted[0] << " " << deleted[1] << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}