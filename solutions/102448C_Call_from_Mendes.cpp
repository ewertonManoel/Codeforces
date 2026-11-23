// Problem: 102448C - Call from Mendes
// Contest: 102448
// Language: C++20 (GCC 13-64) | Time: 187 ms | Memory: 168900 KB
// Problem Link: https://codeforces.com/gym/102448/problem/C
// Submission: https://codeforces.com/gym/102448/submission/399638076

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int INF = 1e9;

struct Trie {
    vector<array<int, 26>> nxt;
    vector<pii> best, index;
    vector<int> path, end_cnt, letter;
    Trie(int q) : nxt(1), best(1, {-1, -1}), index(q + 1), letter(1), path(1, -1), end_cnt(1, 0) {}

    void insert(const string& s, int id) {
        int u = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (!nxt[u][idx]) {
                nxt[u][idx] = nxt.size();
                nxt.push_back({}); 
                best.push_back({-1, -1});
                path.push_back(u);
                letter.push_back(idx);
                end_cnt.push_back(0);
            }
            u = nxt[u][idx];
        }
        index[id] = {u, (int)s.size()};
        end_cnt[u]++;
        int cur = best[u].first;
        best[u] = {id, -1};
        while(u != 0) {
            int p = path[u];
            if(best[p].first == -1 || best[p].first == cur) best[p] = {id, letter[u]};
            else {
                int old = best[p].first;
                if((int)s.size() > index[old].second || (int)s.size() == index[old].second && letter[u] > best[p].second) break;
                cur = old;
                best[p] = {id, letter[u]};
            }
            u = p;
        }
    }

    void erase(int id) {
        int u = index[id].first;
        end_cnt[u]--;
        while(u != -1) {
            if(end_cnt[index[best[u].first].first] > 0) break;
            int minimum = INF;
            int i = 0; int node = 0;
            for(int idx = 0; idx < 26; idx++) {
                if(nxt[u][idx] == 0 || best[nxt[u][idx]].first == -1) continue;
                if(index[best[nxt[u][idx]].first].second < minimum) {
                    minimum = index[best[nxt[u][idx]].first].second;
                    node = best[nxt[u][idx]].first;
                    i = idx;
                }
            }
            best[u] = {node, i};
            if(minimum == INF) best[u] = {-1, -1};
            u = path[u];
        }
    }

    int query(const string& s) {
        int u = 0;
        for (char c : s) {
            u = nxt[u][c - 'a'];
            if(u == 0) return -1;
        }
        return best[u].first;
    }
};

void solve() {
    int q; cin >> q;
    Trie t(q);
    for(int id = 1; id <= q; id++) {
        int x; cin >> x;
        if(x == 1) {
            string s; cin >> s;
            t.insert(s, id);
        }
        else if(x == 2) {
            int idx; cin >> idx;
            t.erase(idx);
        }
        else {
            string s; cin >> s;
            cout << t.query(s) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int t = 1; while(t--) solve();
}
