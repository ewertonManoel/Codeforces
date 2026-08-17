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
unordered_set<ll> s;
ll ans;
int n, m, x, y, i, j;
vll a, b;

void mv_a() {
    ans += a[i];
    s.insert(a[i]);
    i--; n--;    
}
void mv_b() {
    ans += b[j];
    s.insert(b[j]);
    j--; m--;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        s.clear();
        cin >> n >> m >> x >> y;
        a.assign(x, 0); b.assign(y, 0);
        for(int i = 0; i < x; i++) cin >> a[i];
        for(int i = 0; i < y; i++) cin >> b[i];
        i = x-1; j = y-1; ans = 0;
        bool flag = true;
        while(flag) {
            while(i != -1 && s.find(a[i]) != s.end()) i--;
            while(j != -1 && s.find(b[j]) != s.end()) j--;
            if(i == -1 || j == -1) break;
            if(a[i] > b[j]) mv_a();
            else if(a[i] < b[j]) mv_b();
            else {
                if((i-n) >= 0 && (j-m) >= 0) {
                    if(a[(i-n)] > b[(j-m)]) mv_b();
                    else mv_a();
                }
                else if((i-n) >= 0) mv_b();
                else mv_a();
            }
            if(n == 0 || m == 0) flag = false;
        }
        if(!flag) {
            n--; m--;
        }
        while(i != -1 && n > 0) {
            if(s.find(a[i]) == s.end()) mv_a();
            else i--;
        }
        while(j != -1 && m > 0) {
            if(s.find(b[j]) == s.end()) mv_b();
            else j--;
        }
        cout << ans << '\n';
    }
}