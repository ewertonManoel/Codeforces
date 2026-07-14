#include <bits/stdc++.h>

using namespace std;

#define fast_io() ios::sync_with_stdio(false); cin.tie(nullptr)
const int MAX_NODES = 10000 * 12 * 26 + 5;

int trie[MAX_NODES][26];
int words[MAX_NODES];
int sz = 0;

void add(string s) {
    int u = 0;
    for(char ch : s) {
        int c = ch - 'a';
        if(trie[u][c] == 0) trie[u][c] = ++sz;
        u = trie[u][c];
    }
    words[u]++;
}

bool dfs(int maximum, int u, string& word) {
    if(words[u] == maximum) return true;
    for(int c = 0; c < 26; c++) {
        if(trie[u][c] != 0) {
            word += 'a' + c;
            if(dfs(maximum, trie[u][c], word)) return true;
            word.pop_back();
        }
    }
    return false;
}

int main() {
    fast_io();
    int n; cin >> n;
    int c; cin >> c;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        int index = s.find('*');
        for(int i = 0; i < 26; i++) {
            s[index] = 'a' + i;
            add(s);
        }
    }
    int maximum = 0;
    for(int value = 0; value <= sz; value++) maximum = max(maximum, words[value]);
    string word = "";
    dfs(maximum, 0, word);
    cout << word << " " << maximum << '\n';
}