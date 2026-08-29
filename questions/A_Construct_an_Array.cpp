#include <bits/stdc++.h>

using namespace std;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        for(int i = 1; i <= n; i++) {
            cout << n + i << " ";
        }
        cout << '\n';
    }
}