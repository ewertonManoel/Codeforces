#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;

#define pb push_back
#define all(x) (x).begin(), (x).end()

const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        priority_queue<ll, vector<ll>, greater<ll>> a, a2;
        priority_queue<pll, vector<pll>, greater<pll>> b, c;
        vector<int> v; 
        v.assign(m, 0);
        for(int i = 0; i < n; i++) {
            ll x; cin >> x;
            a.push(x);
        }
        for(int i = 0; i < m; i++) cin >> v[i];
        for(int i = 0; i < m; i++) {
            ll x; cin >> x;
            if(x != 0) b.push({v[i], x});
            else c.push({v[i], x});
        }
        int kills = 0;
        while(!a.empty() && !b.empty()) {
            ll sword = a.top(); a.pop();
            ll monster = b.top().first;
            ll other_sword = b.top().second;
            if(sword >= monster) {
                b.pop();
                a.push(max(sword, other_sword));
                kills++;
            }
            else a2.push(sword);
        }
        while(!a2.empty()) {
            a.push(a2.top()); a2.pop();
        }
        while(!a.empty() && !c.empty()) {
            ll sword = a.top(); a.pop();
            ll monster = c.top().first;
            ll other_sword = c.top().second;
            if(sword >= monster) {
                c.pop();
                kills++;
            }
        }
        cout << kills << '\n';
    }
}