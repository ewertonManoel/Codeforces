#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define INF 1e18
const ll MOD = 1e9 + 7;
vector<vector<double>> memo;
int n, prob; double p;

double dp(int i, int j) {
    if(i > 2026 || i == j) return 0;
    if(memo[i][j] != -1) return memo[i][j];
    double pi = (i == 2026) ? 0 : p;
    double rep = (double) j / i, rep2 = (double) j / (i + 1);
    double c = pi * rep2 * dp(i+1, j);
    double c2 = (1 - pi) * (1-rep) * dp(i, j+1);
    double c3 = pi * (1-rep2) * dp(i+1, j+1);
    return memo[i][j] = (1 + c + c2 + c3) / (1 - (1 - pi) * rep);
}
void solve() {
    cin >> n >> prob;
    p = (double)prob / 100;
    memo.assign(2027, vector<double>(2027, -1));
    cout << fixed << setprecision(10) << dp(n, 0) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}