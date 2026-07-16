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
vector<int> vect;

int main() {
    fast_io();
    int b; cin >> b;
    int l; cin >> l;
    b++;
    int evenSum = 0;
    int oddSum = 0;
    vect.pb(0);
    for(int i = 0; i < l; i++) {
        int x; cin >> x;
        vect.pb(x);
    }
    int n = vect.size();
    for(int i = 1; i < n; i++) {
        if(i % 2 == 0) evenSum = (evenSum + vect[i]) % b;
        else oddSum = (oddSum + vect[i]) % b;
    }
    bool order = (evenSum > oddSum ? true : false);
    int number = abs(evenSum - oddSum) % b;
    int number2 = b - number;
    int result = -1;
    int index = -1;
    if(number == 0) {
        result = 0;
        index = 0;
    }
    else {
        for(int i = 1; i < n; i++) {
            int j = (order ? i : i - 1);
            if(j % 2 == 0 && vect[i] >= number) {
                result = vect[i] - number;
                index = i;
                break;
            }
            else if(j % 2 != 0 && vect[i] >= number2) {
                result = vect[i] - number2;
                index = i;
                break;
            }
        }
    }
    cout << index << " " << result << '\n';
}