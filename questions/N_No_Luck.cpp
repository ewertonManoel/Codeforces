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

vector<int> bit;
vector<pii> slots;
vector<array<int, 4>> competitors;
vector<int> ans;

void update(int idx) {
    int n = bit.size();
    for(; idx < n; idx += idx & (-idx)) {
        bit[idx] += 1;
    }
}
int query(int idx) {
    int sum = 0;
    for(; idx > 0; idx -= idx & (-idx)) {
        sum += bit[idx];
    }
    return sum;
}

int range_query(int l, int r) {
    return (query(r) - query(l-1));
}

int main() {
    fast_io();
    int y; cin >> y;
    int n; cin >> n;
    for(int i = 1; i <= y; i++) {
        int x; cin >> x;
        slots.pb({x, i});
    }
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        int p; cin >> p;
        int f; cin >> f;
        if(slots[a - 1].first >= p) p = INF;
        competitors.pb({p, a, f, i});
    }
    bit.assign(y + 1, 0);
    sort(all(slots)); reverse(all(slots));
    ans.resize(n);
    sort(all(competitors)); reverse(all(competitors));
    int l = 0;
    for(auto& [pos, year, after_year, idx] : competitors) {
        int r = l;
        for(; r < y; r++) {
            if(slots[r].first < pos) {
                break;
            }
            update(slots[r].second);
        }
        ans[idx] = range_query(year + 1, year + after_year);
        l = r;
    }
    for(int i : ans) cout << i << '\n';
}