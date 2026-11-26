// Problem: 105791J - Judge Fail
// Contest: 105791
// Language: C++20 (GCC 13-64) | Time: 125 ms | Memory: 6400 KB
// Problem Link: https://codeforces.com/gym/105791/problem/J
// Submission: https://codeforces.com/gym/105791/submission/399848107

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

int n, w;
vector<vector<ll>> dp;
vector<pll> items;
const ll LINF = 1e18;

map<int, int> mp;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> competitor(m);
    vector<int> freq(1e6 + 10, 0);
    vector<double> verdicts(k, 0);

    for(int i = 0; i < m; i++) {
        int x; cin >> x;
        for(int j = 0; j < x; j++) {
            int val; cin >> val; val--;
            competitor[i].push_back(val);
        }
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x; x--;
        freq[x]++;
    }

    for(int i = 0; i < m; i++) {
        for(int j : competitor[i]) {
            verdicts[j] += (double)freq[i] / competitor[i].size();
        }
    }
    
    cout << fixed << setprecision(7);
    for(double d : verdicts) cout << d << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) {solve();}
}
