#include <bits/stdc++.h>

#define pb push_back

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const int sz = 500005;
vector<bool> dp;
void pre_compute() {
    dp.assign(sz, true);
    dp[0] = false; int last = 0;
    for(int i = 2; i < sz - 1; i++) {
        int count = (i + 1) / 2;
        if(i - count > last) {
            dp[i] = false;
            last = i;
        }
    }
}
void solve() {
    int n; cin >> n;
    if(dp[n]) cout << "mastermei\n";
    else cout << "the greatest\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    pre_compute();
    int t = 1; cin >> t; while(t--) {solve();}
}