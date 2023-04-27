#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<vector<int>> matrix;
int INF = 1e9;

void floyd_warshall(){
    for (int p = 0; p < n; p++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((abs(i - p) <= k) && (abs(j - p) <= k)) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][p] + matrix[p][j]);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    matrix.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i].push_back(0);
            } else {
                matrix[i].push_back(INF);
            }
        }
    }

    int source, destination, weight;
    for (int i = 0; i < m; i++) {
        cin >> source >> destination >> weight;
        --destination;
        --source;
        matrix[source][destination] = weight;
    }

    int q;
    cin >> q;
    floyd_warshall();

    for (int i = 0; i < q; i++) {
        cin >> source >> destination;
        --source;
        --destination;
        if (matrix[source][destination] != INF) {
            cout << matrix[source][destination] << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}