#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define ff first
#define ss second

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        unordered_map<int, int> mp;
        int n; cin >> n;
        int k; cin >> k;
        for(int i = 0; i < n; i++) {
            int x; cin >> x;
            mp[x]++;
        }
        bool change = true;
        int count = 0;
        while(!mp.empty()) {
            if(k >= n && (k - n) % mp.size() == 0 && change) {
                count++;
                change = false;
            }
            for(auto it = mp.begin(); it != mp.end(); ) {
                n--;
                it->second--;
                if(it->second == 0) {
                    it = mp.erase(it);
                    change = true;
                }
                else it++;
            }
        }
        cout << count << '\n';
    }
}