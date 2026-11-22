// Problem: 101550B - Bless You Autocorrect!
// Contest: 101550
// Language: C++20 (GCC 13-64) | Time: 109 ms | Memory: 163300 KB
// Problem Link: https://codeforces.com/gym/101550/problem/B
// Submission: https://codeforces.com/gym/101550/submission/399422201

#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
int INF = 1e9;

struct Trie {
    vector<array<int, 26>> nxt;
    vector<int> pref, end_cnt;
    Trie() : nxt(1), pref(1, 0), end_cnt(1, 0) {}

    void insert(const string& s) {
        int u = 0;
        bool leaf = true;
        for (char c : s) {
            leaf = false;
            int idx = c - 'a';
            if (!nxt[u][idx]) {
                leaf = true;
                nxt[u][idx] = nxt.size();
                nxt.push_back({}); pref.push_back(0); end_cnt.push_back(0);
            }
            u = nxt[u][idx];
            pref[u]++;
        }
        if(leaf) end_cnt[u]++;
    }

    int search(string s) {
        int i = 1, prev_i = 1, ans = 0, sz = 0, last = 0;
        int u = nxt[0][s[0] - 'a'];
        if(!u) return s.size();
        bool different = false;
        while(true) {
            if(end_cnt[u] > 0) {
                if(!different) last = u;
                ans += 1 + min(i - prev_i, 1 + sz - (i - prev_i));
                if(i == s.size()) break;
                u = nxt[last][s[i] - 'a'];
                if(!u) return ans + (s.size() - i);
                i++;
                prev_i = i;
                sz = 0;
                different = false;
                continue;
            }
            int minimum = INF, letter = 0;
            for(int j = 0; j < 26; j++) {
                if(nxt[u][j] != 0 && nxt[u][j] < minimum) {
                    minimum = nxt[u][j];
                    letter = j;
                }
            }
            sz++;
            if(i < s.size() && s[i] - 'a' == letter && !different) i++;
            else if(!different) {
                last = u;
                different = true;
            }
            u = minimum;
        }
        return ans;
    }
};

void solve() {
    int n, q; cin >> n >> q;
    Trie trie;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        trie.insert(s);
    }
    while(q--) {
        string s; cin >> s;
        cout << trie.search(s) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}
