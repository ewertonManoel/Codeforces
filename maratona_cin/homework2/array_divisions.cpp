#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool tryValue(vector<ll>& vect, ll maximum, int k) {
    int div = 0, n = vect.size(); ll sum = 0;
    for(int r = 0; r < n; r++) {
        if(vect[r] > maximum) return false;
        if(sum + vect[r] > maximum) {
            div++;
            sum = 0;
        }
        sum += vect[r];
    }
    if(div + 1 > k) return false;
    return true;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> vect(n, 0);
    for(int i = 0; i < n; i++) cin >> vect[i];
    ll l = 0, r = accumulate(vect.begin(), vect.end(), 0LL);
    while(l < r) {
        ll mid = l + (r - l) / 2;
        if(tryValue(vect, mid, k)) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}