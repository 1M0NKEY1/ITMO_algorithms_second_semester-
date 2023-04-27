#include <iostream>
#include <vector>

using namespace std;

void floyd(int N, vector<vector<int>> matrix, int max_i) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (matrix[j][i] == -1 or matrix[i][k] == -1) {
                    continue;
                } else if (matrix[j][i] != -1 and matrix[i][k] != -1 and matrix[j][k] == -1) {
                    matrix[j][k] = matrix[j][i] + matrix[i][k];
                } else if (matrix[j][i] != -1 and matrix[i][k] != -1 and matrix[j][k] != -1) {
                    matrix[j][k] = min(matrix[j][k], matrix[j][i] + matrix[i][k]);
                }
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > max_i) {
                max_i = matrix[i][j];
            }
        }
    }

    cout << max_i;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> matrix(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++) {
        matrix[i][i] = 0;
    }

    int start, end, length;
    for (int i = 0; i < M; i++) {
        cin >> start >> end >> length;
        matrix[start - 1][end - 1] = length;
        matrix[end - 1][start - 1] = length;
    }

    int max_i = -100;
    floyd(N, matrix, max_i);

    return 0;
}
