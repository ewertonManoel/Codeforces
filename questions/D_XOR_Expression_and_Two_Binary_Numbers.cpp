#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int t; cin >> t;
    while(t--) {
        int n, k; cin >> n >> k;
        string s1, s2; cin >> s1 >> s2;
        ll n1 = s1.size(), n2 = s2.size();
        ll m = max(n1, n2);
        ll a_ones = 0, b_ones = 0, c_ones = 0;
        
        for(int i = 0; i < n; i++) {
            if(s1[i] == '1') a_ones++;
            if(s2[i] == '1') b_ones++;
            if(s1[i] != s2[i]) c_ones++;
        }
        
        ll a_value = a_ones * (n1 - a_ones); 
        ll b_value = b_ones * (n2 - b_ones); 
        ll c_value = c_ones * (m - c_ones);
        
        ll a_count, b_count, c_count;
        ll sz = (1 << k) + 1;
        if(k&1) a_count = b_count = c_count = sz/3;
        else {
            a_count = b_count = (sz + 2) / 3;
            c_count = sz / 3;
        }
        
        ll result = (a_count * a_value) + (b_count * b_value) + (c_count * c_value);
        cout << result << '\n';
    }
}