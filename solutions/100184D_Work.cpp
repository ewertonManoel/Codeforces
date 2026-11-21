// Problem: 100184D - Work
// Contest: 100184
// Language: C++20 (GCC 13-64) | Time: 92 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/100184/problem/D
// Submission: https://codeforces.com/gym/100184/submission/399414596

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
const ll INF = 1e15;

vector<int> primes, spf;

void sieve(int n) {
    primes.clear();
    spf.resize(n + 1);
    iota(spf.begin(), spf.end(), 0);

    for(int i = 2; i * i <= n; i++) {
        if(spf[i] != i) continue;
        for(int j = i * i; j <= n; j += i) {
            if(spf[j] == j) {
                spf[j] = i;
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        if(spf[i] == i) {
            primes.push_back(i);
        }
    }
}

bool is_prime(int x) {
    return x >= 2 && spf[x] == x;
}

void solve() {
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<int> v1, v2;
    int idx = 0;
    for(int i = 1; i <= n; i++) {
        if(idx == m) break;
        if((s[idx] == 'Y' && is_prime(i)) || (s[idx] == 'N' && !is_prime(i))) {
            v1.push_back(i);
            idx++;
        }
    }
    idx = m - 1;
    for(int i = n; i >= 1; i--) {
        if(idx == -1) break;
        if(s[idx] == 'Y' && is_prime(i) || s[idx] == 'N' && !is_prime(i)) {
            v2.push_back(i);
            idx--;
        }
    }
    reverse(v2.begin(), v2.end());
    int cnt = 0;
    for(int i = 0; i < v1.size(); i++) {
        if(v1[i] == v2[i]) cnt++;
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    sieve(1e5);
    int t = 1; while(t--) solve();
}
