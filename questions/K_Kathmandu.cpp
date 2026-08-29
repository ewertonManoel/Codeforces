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
    int T; cin >> T;
    int D; cin >> D;
    int M; cin >> M;
    int prevTime = 0;
    int curTime;
    char ans = 'N';
    for(int i = 0; i < M; i++) {
        cin >> curTime;
        if(curTime - prevTime >= T) ans = 'Y';
        prevTime = curTime;
    }
    if(D - prevTime >= T) ans = 'Y';
    cout << ans << '\n';
}