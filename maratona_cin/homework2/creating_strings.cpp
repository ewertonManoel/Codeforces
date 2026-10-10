#include <bits/stdc++.h>

using namespace std;

void solve() {
    string s; cin >> s;
    sort(s.begin(), s.end());
    vector<string> v;
    do {
        v.push_back(s);
    } while(next_permutation(s.begin(), s.end()));
    cout << v.size() << '\n';
    for(string s : v) cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}