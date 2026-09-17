#include <bits/stdc++.h>

using namespace std;

#define INF 1e6

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        unordered_map<int, int> mp; mp[0] = -1;
        string s; cin >> s;
        int prefix = 0, a = 0, b = 0, ans = INF;
        for(char c : s) (c == 'a') ? a++ : b++;
        int sum = a - b; 
        if(sum == 0) ans = 0;
        else for(int i = 0; i < n; i++) {
            int val = (s[i] == 'a') ? 1 : -1;
            prefix += val;
            if(mp.find(prefix - sum) != mp.end()) ans = min(ans, i - mp[prefix - sum]);
            mp[prefix] = i;
        }
        if(ans >= n) ans = -1;
        cout << ans << '\n';
    }
}