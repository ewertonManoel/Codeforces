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
vector<pair<int, int>> vect;

int main() {
    fast_io();
    int n; cin >> n;
    int direction = 0;
    vect.pb({0, 0});
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        int d; cin >> d;
        int difference = 0;
        for(auto& [time, dir] : vect) {
            if(t < time && d == dir) {
                difference = t + 10 - time;
            }
            if(difference > 0) time += difference;
        }
        if(vect.size() > 2) vect.erase(vect.begin());
        if(difference == 0) {
            auto& [time, dir] = vect.back();
            if(t < time && d != dir) vect.pb({time + 10, d});
            else if(t > time) vect.pb({t + 10, d});
        }
    }
    int ans = vect.back().first;
    cout << ans << '\n';
}