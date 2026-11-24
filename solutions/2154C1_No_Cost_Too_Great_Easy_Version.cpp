// Problem: 2154C1 - No Cost Too Great (Easy Version)
// Contest: 2154 | Rating: 1400 | Tags: greedy, implementation, math, number theory
// Language: C++20 (GCC 13-64) | Time: 1718 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/contest/2154/problem/C1
// Submission: https://codeforces.com/contest/2154/submission/399702383

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool get_divisors(int n, set<int>& divisors) {
    for(int i = 1; (ll)i * i <= (ll)n; i++) {
        if(n % i != 0) continue;
        if(divisors.find(i) != divisors.end()) return true;
        if(divisors.find(n / i) != divisors.end()) return true;
        if(i != 1) divisors.insert(i);
        if(n / i != 1) divisors.insert(n / i);
    }
    return false;
}

bool get_divisors1(int n, set<int>& divisors0, set<int>& divisors1) {
    int m = n + 1;
    vector<int> temp;
    for(int i = 1; (ll)i * i <= (ll)m; i++) {
        if(n % i == 0) { 
            if(divisors1.find(i) != divisors1.end()) return true;
            if(divisors1.find(n / i) != divisors1.end()) return true;
            if(i != 1) temp.push_back(i);
            if(n / i != 1) temp.push_back(n / i);
        }
        if(m % i == 0) {
            if(divisors0.find(i) != divisors0.end()) return true;
            if(divisors0.find(m / i) != divisors0.end()) return true;
            if(i != 1) divisors1.insert(i);
            if(m / i != 1) divisors1.insert(m / i);
        }
    }
    for(int i : temp) divisors0.insert(i);
    return false;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n, 0), b(n, 1);
    set<int> divisors, divisors1;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++) {
        if(get_divisors(a[i], divisors)) {
            cout << 0 << '\n';
            return;
        }
    }
    divisors.clear();
    for(int i = 0; i < n; i++) {
        if(get_divisors1(a[i], divisors, divisors1)) {
            cout << 1 << '\n';
            return;
        }
    }
    cout << 2 << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; cin >> t; while(t--) solve();
}
