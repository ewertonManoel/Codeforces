#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

bool check(vector<vector<char>>& matrix, int row, int col, char c) {
    for(int i = 0; i < 9; i++) {
        int st_row = row / 3 * 3, st_col = col / 3 * 3, idx_row = i / 3, idx_col = i % 3;
        if(matrix[row][i] == c) return false;
        if(matrix[i][col] == c) return false;
        if(matrix[st_row + idx_row][st_col + idx_col] == c) return false;
    }
    return true;
}

bool sudoku(vector<vector<char>>& matrix, int i = 0, int j = 0) {
    if(j == 9) return sudoku(matrix, i + 1, 0);
    if(i == 9) return true;
    if(matrix[i][j] == '0') {
        for(char c = '1'; c <= '9'; c++) {
            if(check(matrix, i, j, c)) {
                matrix[i][j] = c;
                if(sudoku(matrix, i, j + 1)) return true;
                matrix[i][j] = '0';
            }
        }
        return false;
    }
    else return sudoku(matrix, i, j + 1);
}
void solve() {
    vector<vector<char>> matrix(9, vector<char>(9));
    for(int i = 0; i < 9; i++) for(int j = 0; j < 9; j++) {
        cin >> matrix[i][j];
    }
    if(sudoku(matrix)) {
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) cout << matrix[i][j] << " ";
            cout << '\n';
        }
    }
    else cout << "No solution" << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; cin >> t; while(t--) solve();
}