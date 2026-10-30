#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

vector<vector<ll>> dp;
string s1, s2;
int n, m;

ll edit(int i, int j) {
    if(i == n) return m - j;
    if(j == m) return n - i;
    if(dp[i][j] != -1) return dp[i][j];
    if(s1[i] == s2[j]) return dp[i][j] = edit(i + 1, j + 1);
    else return dp[i][j] = 1 + min({edit(i+1, j+1), edit(i, j+1), edit(i+1, j)});
}
void solve() {
    cin >> s1 >> s2;
    n = s1.size(), m = s2.size();
    dp.assign(n, vector<ll>(m, -1));
    cout << edit(0, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}