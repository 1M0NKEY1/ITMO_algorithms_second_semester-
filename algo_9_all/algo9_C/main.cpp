#include <iostream>
#include <vector>

using namespace std;

void browse(int n, int m, vector<vector<int>>& matrix, int max_n, int max_m) {
    if (matrix[n][m] == 0) {
        matrix[n][m] = 1;
    }
    if (n != 0 and matrix[n - 1][m] != 1) {
        browse(n - 1, m, matrix, max_n, max_m);
    }
    if (m != 0 and matrix[n][m - 1] != 1) {
        browse(n, m - 1, matrix, max_n, max_m);
    }
    if (n + 1 < max_n and matrix[n + 1][m] != 1) {
        browse(n + 1, m, matrix, max_n, max_m);
    }
    if (m + 1 < max_m and matrix[n][m + 1] != 1) {
        browse(n, m + 1, matrix, max_n, max_m);
    }
}

int main() {
    int n;
    int m;
    cin >> n >> m;

    vector<vector<int>> matrix;

    for (int i = 0; i < n; i++) {
        vector<int> line;
        for (int j = 0; j < m; j++) {
            char position;
            cin >> position;
            if (position == '.') {
                line.emplace_back(0);
            } else if (position == '#') {
                line.emplace_back(1);
            }
        }
        matrix.emplace_back(line);
    }

    int counter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                counter += 1;
                browse(i, j, matrix, n, m);
            }
        }
    }

    cout << counter;
    return 0;
}
