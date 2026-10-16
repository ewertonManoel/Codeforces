#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

#define pb push_back

void solve() {
    int n; cin >> n;
    string last;
    vector<vector<int>> adj(26, vector<int>());
    vector<int> indegree(26, 0);
    vector<char> order;
    bool possible = true;
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        if(i > 0) {
            bool dif = false;
            for(int j = 0; j < min(last.size(), s.size()); j++) {
                if(last[j] != s[j]) {
                    dif = true;
                    adj[last[j] - 'a'].pb(s[j] - 'a');
                    indegree[s[j] - 'a']++;
                    break;
                }
            }
            if(!dif && last.size() > s.size()) possible = false;
        }
        last = s;
    }
    queue<int> q;
    for(int i = 0; i < 26; i++) if(indegree[i] == 0) q.push(i);
    while(!q.empty()) {
        int letter = q.front(); q.pop();
        order.pb('a' + letter);
        for(auto v : adj[letter]) {
            indegree[v]--;
            if(indegree[v] == 0) q.push(v);
        }
    }
    if(order.size() < 26) possible = false;
    if(!possible) cout << "Impossible";
    else {
        for(char c : order) cout << c;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) { solve(); }
}