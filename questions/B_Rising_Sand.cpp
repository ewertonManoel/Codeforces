#include <bits/stdc++.h>

using namespace std;

int count;
vector<int> v;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, k, count = 0; cin >> n >> k;
        vector<int> v(n, 0);
        for(int i = 0; i < n; i++) cin >> v[i];
        for(int i = 1; i < n-1; i++) if(v[i] > v[i-1] + v[i+1]) count++;
        if(k == 1) count = (n - 1) / 2;
        cout << count << '\n';
    }
}
/*
3 : 1
4 : 1
5 : 2
6 : 2
7 : 3
8 : 3
*/