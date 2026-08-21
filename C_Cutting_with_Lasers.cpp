#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const int sz = 1005;
bool v_wall[sz][sz], h_wall[sz][sz], visited[sz][sz];
int h[4] = {-1, 1, 0, 0};
int v[4] = {0, 0, -1, 1};
int flood_fill(int xc, int yc) {
    stack<pii> st;
    st.push({xc, yc});
    int area = 0;
    while(!st.empty()) {
        int x = st.top().first; int y = st.top().second; st.pop();
        if(x < 0 || x >= sz || y < 0 || y >= sz) continue;
        if(visited[x][y]) continue;
        visited[x][y] = true;
        area++;
        for(int i = 0; i < 4; i++) {
            int nx = x + h[i], ny = y + v[i];
            if(nx < 0 || nx >= sz || ny < 0 || ny >= sz) continue;
            if((v[i] > 0 && !h_wall[ny][nx]) || (v[i] < 0 && !h_wall[y][x]) || 
               (h[i] > 0 && !v_wall[nx][ny]) || (h[i] < 0 && !v_wall[x][y])) st.push({nx, ny});
        }
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    memset(visited, 0, sizeof(visited));
    memset(v_wall, 0, sizeof(v_wall)); memset(h_wall, 0, sizeof(h_wall));
    vector<pii> pts(n+1); 
    for(int i = 0; i <= n; i++) cin >> pts[i].first >> pts[i].second;
    for(int i = 1; i <= n; i++) {
        int x = pts[i].first, prev_x = pts[i-1].first, min_x = min(x, prev_x), max_x = max(x, prev_x);
        int y = pts[i].second, prev_y = pts[i-1].second, min_y = min(y, prev_y), max_y = max(y, prev_y);
        if(x != prev_x) for(int i = min_x; i < max_x; i++) h_wall[y][i] = true; 
        else if(y != prev_y) for(int i = min_y; i < max_y; i++) v_wall[x][i] = true; 
    }
    flood_fill(0, 0);
    int area = 0;
    for(int i = 0; i < sz; i++) for(int j = 0; j < sz; j++) {
        if(!visited[i][j]) area = max(area, flood_fill(i, j));
    }
    cout << area << '\n';
}