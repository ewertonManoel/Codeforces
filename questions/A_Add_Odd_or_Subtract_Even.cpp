#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int a, b; cin >> a >> b;
        int c = a - b, v = 0;
        if((a > b && (c % 2 == 0)) || ((a < b) && (c & 1))) v = 1;
        else if((a > b && (c & 1)) || ((a < b) && (c % 2 == 0))) v = 2;
        cout << v << '\n';
    }
}