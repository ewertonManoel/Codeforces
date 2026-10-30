#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<vector<ll>> dp;
vector<vector<pll>> transiction;
vector<ll> v1, v2;
int n, m;
ll lcs(int i, int j) {
    if(i == n || j == m) return 0;
    if(dp[i][j] != -1) return dp[i][j];
    if(v1[i] == v2[j]) {
        transiction[i][j] = {i + 1, j + 1};
        return dp[i][j] = 1 + lcs(i + 1, j + 1);
    }
    else {
        ll first = lcs(i + 1, j), second = lcs(i, j + 1);
        if(first > second) {
            transiction[i][j] = {i + 1, j};
            return dp[i][j] = first;
        }
        else {
            transiction[i][j] = {i, j + 1};
            return dp[i][j] = second;
        }
    }
}
void solve() {
    cin >> n >> m;
    v1.assign(n, 0); v2.assign(m, 0);
    dp.assign(n, vector<ll>(m, -1));
    transiction.assign(n, vector<pll>(m));
    for(int i = 0; i < n; i++) cin >> v1[i];
    for(int i = 0; i < m; i++) cin >> v2[i];
    cout << lcs(0, 0) << '\n';
    vector<ll> ans;
    int i = 0, j = 0;
    while(i < n && j < m) {
        auto p = transiction[i][j];
        if(p.first == i+1 && p.second == j+1) ans.pb(v1[i]);
        i = p.first, j = p.second;
    }
    for(ll val : ans) cout << val << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}