#include <bits/stdc++.h>

using namespace std;
using ll = long long;


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<ll> v(n, 0);
        vector<vector<ll>> a(n, vector<ll>(m, 0));
        multiset<ll> st;
        int value = m;
        for(int i = 0; i < n; i++) cin >> v[i];
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> a[i][j];
        for(int i = 0; i < n; i++) sort(a[i].begin(), a[i].end());
        for(int i = n-1; i >= 0; i--) {
            for(int j = m-1; j >= 0; j--) {
                st.insert(a[i][j]);
                if(i < n-1) st.erase(st.begin());
            }
            int count = 0;
            for(auto it = st.rbegin(); it != st.rend() && v[i] > 0; it++) {
                v[i] -= *it;
                count++;
            }
            if(v[i] <= 0) value = min(value, count);
        }
        cout << value << '\n';
    }
}