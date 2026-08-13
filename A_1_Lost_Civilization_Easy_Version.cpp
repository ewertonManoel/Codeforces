#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<ll> v(n, 0);
        for(int i = 0; i < n; i++) {
            cin >> v[i];
        }
        ll first = v[0];
        ll last = first;
        int length = 1;
        for(int i = 1; i < n; i++) {
            if(v[i] > first && v[i] <= last + 1) {
                last = v[i];
            }
            else {
                first = v[i];
                last = first;
                length++;
            }
        }
        cout << length << "\n";
    }    
}