#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<pair<string, int>> guesses;
ll p; int n, m;

void check(ll mask) {
    bool ok = true;
    for(auto pp : guesses) {
        int count = 0;
        for(int bit = 0; bit < n; bit++) {
            int bit_password = (mask >> bit) & 1;
            int bit_guess = pp.first[n - (bit + 1)] - '0';
            if(bit_password == bit_guess) count++;
        }
        if(count != pp.second) {
            ok = false;
            break;
        }
    }
    if(ok) p++;
}

void gen(int k, int st, ll mask) {
    if(k == 0) {
        for(int bit = 0; bit < n; bit++) {
            mask ^= ((ll)guesses[0].first[n - (bit + 1)] - '0') << bit;
        }
        check(mask);
        return;
    }
    for(int i = st; i < n; i++) {
        gen(k-1, i + 1, mask & (~(1LL << i)));
    }
}
void solve() {
    cin >> n >> m;
    guesses.clear(); guesses.resize(m);
    for(int i = 0; i < m; i++) {
        string guess; int corrects; cin >> guess >> corrects;
        guesses[i] = {guess, corrects};
    }
    p = 0;
    gen(guesses[0].second, 0, (1LL << n) - 1);
    cout << p << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}