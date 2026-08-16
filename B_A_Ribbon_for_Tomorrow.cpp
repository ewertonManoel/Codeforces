#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int P = 998244353;

//inv(i) mod p = -q * inv(r); 
const int sz = 1000005;
ll inv[sz];
ll fact[sz];
ll invFact[sz];

ll mod(ll a, ll b) {return (((a % b) + b) % b);}
void calculate_inv() {
    inv[1] = 1;
    for(int i = 2; i < sz; i++) inv[i] = mod((-(P / i) * inv[P % i]), P);
}
void calculate_fact() {
    fact[0] = fact[1] = 1;
    for(int i = 2; i < sz; i++) fact[i] = (fact[i-1] * i) % P;
}
void calculate_invFact() {
    invFact[0] = invFact[1] = 1;
    for(int i = 2; i < sz; i++) invFact[i] = (invFact[i-1] * inv[i]) % P;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    calculate_inv();
    calculate_fact();
    calculate_invFact();
    int t; cin >> t;
    while(t--) {
        int len; cin >> len;
        string s; cin >> s;
        int n0, k0, n1, k1;
        n0 = k0 = n1 = k1 = 0;
        char prev = '2';
        for(int i = 0; i < len; i++) {
            if(s[i] == '0') {
                n0++;
                if(s[i] != prev) k0++; 
            }
            else {
                n1++;
                if(s[i] != prev) k1++;
            }
            prev = s[i];
        }
        n0--; k0--; n1--; k1--;
        ll C0 = 1, C1 = 1;
        if(n0 != -1 && n1 != -1) {
            C0 = (fact[n0] * ((invFact[n0 - k0] * invFact[k0]) % P) % P) % P;
            C1 = (fact[n1] * ((invFact[n1 - k1] * invFact[k1]) % P) % P) % P;
        }
        ll ans = (C0 * C1) % P;
        cout << ans << '\n';
    }
}