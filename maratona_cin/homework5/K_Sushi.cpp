#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;
int n;
vector<vector<vector<double>>> memo;

double dp(int one, int two, int three) {
    if(one == 0 && two == 0 && three == 0) return 0;
    if(memo[one][two][three] != -1) return memo[one][two][three];
    double expected = 0;
    if(one >= 1) {
        expected += (double)one / (one + two + three) * dp(one - 1, two, three);
    }
    if(two >= 1) {
        expected += (double)two / (one + two + three) * dp(one + 1, two - 1, three);
    }
    if(three >= 1) {
        expected += (double)three / (one + two + three) * dp(one, two + 1, three - 1);
    }
    return memo[one][two][three] = (double)n / (one + two + three) + expected; 
}
void solve() {
    cin >> n;
    vector<int> sushi(n, 0);
    for(int i = 0; i < n; i++) cin >> sushi[i];
    int one = 0, two = 0, three = 0;
    for(int i = 0; i < n; i++) {
        if(sushi[i] == 1) one++;
        else if(sushi[i] == 2) two++;
        else if(sushi[i] == 3) three++;
    }
    memo.assign(n + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, -1)));
    cout << fixed << setprecision(10) << dp(one, two, three) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}