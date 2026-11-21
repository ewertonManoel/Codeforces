// Problem: 105129L - 15 Prime
// Contest: 105129
// Language: C++20 (GCC 13-64) | Time: 156 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105129/problem/L
// Submission: https://codeforces.com/gym/105129/submission/399413453

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

void solve() {
    int n; cin >> n;
    vector<int> numbers(n, 0);
    for(int i = 0; i < n; i++) cin >> numbers[i];
    sort(numbers.begin(), numbers.end());
    numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());
    int mask = 0;
    ll global_ans = 1e18;
    for(; mask < (1 << 15); mask++) {
        bool ok = true;
        for(int val : numbers) {
            bool found = false;
            for(int bit = 0; bit < 15; bit++) {
                if((mask >> bit) & 1) {
                    if(gcd(primes[bit], val) >= 2) {
                        found = true;
                        break;
                    }
                }
            }
            if(!found) {
                ok = false;
                break;
            }
        }
        if(ok) {
            ll local_ans = 1;
            for(int bit = 0; bit < 15; bit++) {
                if((mask >> bit) & 1) local_ans *= primes[bit];
            }
            global_ans = min(global_ans, local_ans);
        }
    }
    cout << global_ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    sieve(50);
    int t = 1; cin >> t; while(t--) solve();
}
