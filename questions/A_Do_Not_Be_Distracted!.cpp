#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        unordered_set<char> st;
        char prev = '_';
        int n; cin >> n;
        bool susp = false;
        for(int i = 0; i < n; i++) {
            char c; cin >> c;
            if(c != prev && st.find(c) != st.end()) susp = true;
            st.insert(c);
            prev = c;
        }
        if(!susp) cout << "YES\n";
        else cout << "NO\n";
    }
}