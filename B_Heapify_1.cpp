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
        vector<int> nums = {0};
        int n; cin >> n;
        for(int i = 1; i <= n; i++) {
            int x; cin >> x;
            nums.pb(x);
        }
        for(int i = 1; i <= n / 2; i++) {
            if(nums[i] != i) {
                for(int j = 2 * i; j <= n; j *= 2) {
                    if(nums[j] == i) {
                        while(j != i) {
                            swap(nums[j], nums[j / 2]);
                            j /= 2;
                        }
                    }
                }
            }
        }
        bool sorted = true;
        for(int i = 1; i <= n; i++) {
            if(nums[i] != i) {
                sorted = false;
                break;
            }
        }
        if(sorted) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}