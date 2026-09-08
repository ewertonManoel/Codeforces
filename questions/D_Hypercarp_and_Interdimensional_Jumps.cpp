#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int x, y, m, sn, prev_target;
string s;

void build_str(int p, int q, char c, char c2) {
    string s_; int l = m;
    for(int i = 0; i < l; i++) s_ += c;
    int maximum = max(p, q), minimum = min(p, q);
    int i = INF, target = min(minimum + (maximum - minimum) / 2, sn);
    while(i > 0 && target > 0) {
        i = min(target, l--); 
        target -= i;
        s_[i-1] = c2;
    }
    if(target < prev_target) s = s_;
    prev_target = target;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        cin >> x >> y;
        s = "";
        prev_target = INF;
        m = (sqrt(1 + 8*(x + y)) - 1) / 2;
        sn = (1 + m) * m / 2;
        build_str(sn - x, y, 'X', 'Y');
        build_str(sn - y, x, 'Y', 'X');
        reverse(s.begin(), s.end());
        for(char c : s) cout << c;
        cout << '\n';
    }
}