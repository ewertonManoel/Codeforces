#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
ll p;

bool check(vector<string>& matrix, int row, int col) {
    for(int i = 0; i < 8; i++) {
        if(matrix[row][i] == 'Q') return false;
        if(matrix[i][col] == 'Q') return false;
        if(row+i < 8 && col+i < 8 && matrix[row+i][col+i] == 'Q') return false;
        if(row-i >= 0 && col+i < 8 && matrix[row-i][col+i] == 'Q') return false;
        if(row+i < 8 && col-i >= 0 && matrix[row+i][col-i] == 'Q') return false;
        if(row-i >= 0 && col-i >= 0 && matrix[row-i][col-i] == 'Q') return false;
    }
    return true;
}

void queen(vector<string>& matrix, int i = 0, int j = 0, int count = 0) {
    if(count == 8) {
        p++;
        return;
    }
    if(i == 8) return;
    if(j == 8) {
        queen(matrix, i + 1, 0, count);
        return;
    }
    assert(i < 8 && j < 8);
    if(matrix[i][j] == '.') {
        if(check(matrix, i, j)) {
            matrix[i][j] = 'Q';
            count++;
            queen(matrix, i, j + 1, count);
            matrix[i][j] = '.';
            count--;
        }
    }
    queen(matrix, i, j + 1, count);
}

void solve() {
    p = 0;
    vector<string> matrix(8, "");
    for(int i = 0; i < 8; i++) {
        cin >> matrix[i];
    }
    queen(matrix);
    cout << p << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; while(t--) solve();
}