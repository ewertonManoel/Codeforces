// Problem: 105321A - Advanced tic-tac-toe
// Contest: 105321
// Language: C++20 (GCC 13-64) | Time: 93 ms | Memory: 0 KB
// Problem Link: https://codeforces.com/gym/105321/problem/A
// Submission: https://codeforces.com/gym/105321/submission/399845678

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

char cells[9];
bool restrictions[9][9];

int base_case() {
    if(cells[0] == 'o' && cells[1] == 'o' && cells[2] == 'o'
    || cells[3] == 'o' && cells[4] == 'o' && cells[5] == 'o'
    || cells[6] == 'o' && cells[7] == 'o' && cells[8] == 'o'
    || cells[0] == 'o' && cells[3] == 'o' && cells[6] == 'o'
    || cells[1] == 'o' && cells[4] == 'o' && cells[7] == 'o'
    || cells[2] == 'o' && cells[5] == 'o' && cells[8] == 'o'
    || cells[0] == 'o' && cells[4] == 'o' && cells[8] == 'o'
    || cells[2] == 'o' && cells[4] == 'o' && cells[6] == 'o') {
        return -1;
    }
    if(cells[0] == 'x' && cells[1] == 'x' && cells[2] == 'x'
    || cells[3] == 'x' && cells[4] == 'x' && cells[5] == 'x'
    || cells[6] == 'x' && cells[7] == 'x' && cells[8] == 'x'
    || cells[0] == 'x' && cells[3] == 'x' && cells[6] == 'x'
    || cells[1] == 'x' && cells[4] == 'x' && cells[7] == 'x'
    || cells[2] == 'x' && cells[5] == 'x' && cells[8] == 'x'
    || cells[0] == 'x' && cells[4] == 'x' && cells[8] == 'x'
    || cells[2] == 'x' && cells[4] == 'x' && cells[6] == 'x') {
        return 1;
    }
    for(int i = 0; i < 9; i++) {
        if(cells[i] == '.') return 2;
    }
    return 0;
}

bool valid_move(int mv) {
    if(cells[mv] != '.') return false;
    for(int j = 0; j < 9; j++) {
        if(restrictions[mv][j] == 1 && cells[j] == '.') return false;
    }
    return true;
}

int minimax(bool turn) {
    int base = base_case();
    if(base != 2) return base;
    int best = turn ? -2 : 2;
    for(int i = 0; i < 9; i++) {
        if(!valid_move(i)) continue;
        if(turn) {
            cells[i] = 'x';
            best = max(best, minimax(!turn));
            cells[i] = '.';
        }
        else {
            cells[i] = 'o';
            best = min(best, minimax(!turn));
            cells[i] = '.';
        }
    }
    if(best == -2 || best == 2) return 0;
    return best;
}

void solve() {
    int n; cin >> n;
    for(int i = 0; i < 9; i++) cells[i] = '.';
    memset(restrictions, 0, sizeof(restrictions));
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; a--; b--;
        restrictions[b][a] = 1;
    }
    int result = minimax(1);
    if(result == 0) cout << 'E' << '\n';
    else if(result == 1) cout << 'X' << '\n';
    else cout << 'O' << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}
