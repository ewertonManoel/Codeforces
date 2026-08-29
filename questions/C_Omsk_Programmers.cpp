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

int main() {
    fast_io();
    int t; cin >> t;
    while(t--) {
        int a; cin >> a;
        int b; cin >> b;
        int x; cin >> x;
        int steps = 0;
        while(a != b) {
            if(a > b) {
                if(abs((a / x) - b) < abs(a - b) || abs((a / x) - (b / x)) < abs(a - b) - 1) a /= x;
                else b++;
            }
            else {
                if(abs((b / x) - a) < abs(a - b) || abs((a / x) - (b / x)) < abs(a - b) - 1) b /= x;
                else a++;
            }
            steps++;
        }
        cout << steps << '\n';
    }
}