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
vector<queue<int>> qs;
unordered_map<int, int> people;
vector<int> sad;
int main() {
    fast_io();
    int n; cin >> n;
    int k; cin >> k;
    qs.assign(k + 1, queue<int>());
    people.clear();
    sad.clear();
    int count = 0;
    int last = 0;
    for(int i = 0; i < 2 * n; i++) {
        int type; cin >> type;
        if(type == 1) {
            int person; cin >> person;
            int pos; cin >> pos;
            qs[pos].push(person);
            people[person] = count++;
        }
        else if(type == 2) {
            int pos; cin >> pos;
            int person = qs[pos].front();
            qs[pos].pop();
            if(people[person] < last) {
                sad.pb(person);
            }
            else last = people[person];
            people.erase(person);
        }
    }
    sort(all(sad));
    int sz = sad.size();
    cout << sz << '\n';
    for(int val : sad) {
        cout << val << " ";
    }
}