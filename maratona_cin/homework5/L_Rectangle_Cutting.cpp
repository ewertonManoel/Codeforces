#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define INF 1e9
vector<vector<int>> memo;

int dp(int r, int c) {
    if(r == 0 || c == 0) return 0;
    if(memo[r][c] != INF) return memo[r][c];
    for(int i = 1; i <= r/2; i++) {
        memo[r][c] = min(memo[r][c], dp(r-i, c) + dp(i, c) + 1);
    }
    for(int j = 1; j <= c/2; j++) {
        memo[r][c] = min(memo[r][c], dp(r, c-j) + dp(r, j) + 1);
    }
    return memo[r][c];
}

void solve() {
    int n, m; cin >> n >> m;
    memo.assign(n + 1, vector<int>(m + 1, INF));
    for(int i = 0; i <= min(n, m); i++) memo[i][i] = 0;
    cout << dp(n, m) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}