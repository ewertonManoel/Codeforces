// Problem: 2048C - Kevin and Binary Strings
// Contest: 2048 | Rating: 1200 | Tags: bitmasks, brute force, greedy, implementation, strings
// Language: C++20 (GCC 13-64) | Time: 46 ms | Memory: 70900 KB
// Problem Link: https://codeforces.com/contest/2048/problem/C
// Submission: https://codeforces.com/contest/2048/submission/399832772

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
const ll INF = 1e18;

struct Trie {
    vector<array<int, 2>> nxt;
    vector<int> pref, end_cnt;
    Trie() : nxt(1), pref(1, 0), end_cnt(1, 0) {}

    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int idx = c - '0';
            if (!nxt[u][idx]) {
                nxt[u][idx] = nxt.size();
                nxt.push_back({}); pref.push_back(0); end_cnt.push_back(0);
            }
            u = nxt[u][idx];
            pref[u]++;
        }
        end_cnt[u]++;
    }

    string find(const string& s) {
        int u = 0;
        string word;
        for(char c : s) {
            int idx = c - '0';
            int idx_rev = idx ^ 1;
            char c_rev = idx_rev + '0';
            if(nxt[u][idx_rev]) {
                word += c_rev;
                u = nxt[u][idx_rev];
            }
            else {
                word += c;
                u = nxt[u][idx];
            }
        }
        return word;
    }
};

void solve() {
    string s; cin >> s; int n = s.size();
    cout << 1 << " " << n << " ";
    int i = 0;
    for(; i < n; i++) if(s[i] == '0') break;
    string target = s.substr(i);
    if(target.size() == 0) {
        cout << 1 << " " << 1 << '\n';
        return;
    }
    int sub_sz = target.size();
    Trie t;
    int best = 0;
    for(int l = 0; l <= n - sub_sz; l++) {
        if(s[l] == '1') t.insert(s.substr(l, sub_sz));
    }
    string found = t.find(target);
    for(int l = 0; l <= n - sub_sz; l++) {
        if(s[l] == '1') {
            string cur = s.substr(l, sub_sz);
            if(cur == found) {
                cout << l + 1 << " " << l + sub_sz << '\n';
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; cin >> t; while(t--) solve();
}
