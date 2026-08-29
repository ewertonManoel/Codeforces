#include<bits/stdc++.h>

using namespace std;
using ll = long long;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n; n *= 2;
        ll k; cin >> k;
        string s; cin >> s;
        int red = 0; int blue = 0;
        for(int i = 0; i < n; i++) {
            if(s[i] == '1') {
                if(s[(i+1)%n] == '0') {
                    if(i&1) blue++;
                    else red++;
                }
                else {
                    if(i&1) red++;
                    else blue++;
                }
            }
        }
        cout << red << " " << blue << "\n";
    }
}