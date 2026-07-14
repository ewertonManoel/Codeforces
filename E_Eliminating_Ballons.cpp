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
unordered_map<int, int> arrows;

vector<int> vect;
int main() {
    fast_io();
    int count = 0;
    int x; cin >> x;
    for(int i = 0; i < x; i++) {
        int y; cin >> y;
        if(arrows[y] > 0) arrows[y]--;
        else count++;
        arrows[y - 1]++;
    }
    cout << count << '\n';
}