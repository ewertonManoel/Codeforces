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

int deck[11] = {0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 16};
int main() {
    fast_io();
    int n; cin >> n;
    int john_points = 0;
    int mary_points = 0;
    for(int i = 0; i < 4 + n; i++) {
        int y; cin >> y;
        int x = (y > 10 ? 10 : y);
        if(i < 2) john_points += x;
        else if(i < 4) mary_points += x;
        else {
            john_points += x;
            mary_points += x;
        }
        deck[x]--;
    }
    int win1 = 23 - mary_points, win2 = INF;
    if(win1 > 10 || deck[win1] == 0) win1 = INF;
    if(mary_points < john_points) {
        int difference = john_points - mary_points;
        int value = 24 - john_points;
        for(int i = value; i < value + difference; i++) {
            if(i > 10) break;
            if(deck[i] > 0) {
                win2 = i;
                break;
            }
        }
    }
    if(win1 == INF && win2 == INF) cout << -1 << '\n';
    else cout << min(win1, win2) << '\n';
}