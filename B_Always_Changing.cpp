#include <bits/stdc++.h>
using namespace std;

#define fast_io ios::sync_with_stdio(false); cin.tie(nullptr)

int main() {
    fast_io;
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        int zero = 0, one = 0, zeroBadPairs = 0, oneBadPairs = 0;
        if(s[0] == '0') zero++;
        else one++;
        for(int i = 1; i < n; i++) {
            if(s[i] == s[i-1]) {
                if(s[i] == '0') zeroBadPairs++;
                else oneBadPairs++;
            }

            if(s[i] == '0') zero++;
            else one++;
        }

        int minimum = min(zero, one);
        int ans = max(zeroBadPairs, oneBadPairs);
        ans = ans * 2 - 1;
        if(zeroBadPairs == oneBadPairs) ans++;
        if(abs(zero - one) > 2) cout << -1 << '\n';
        else cout << ans << '\n';
    }
}