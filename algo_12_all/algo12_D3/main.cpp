#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 110;

int n, m, q;
bool visited[MAXN][MAXN];
vector<int> graph[MAXN * MAXN];
int mt[MAXN * MAXN];
bool used[MAXN * MAXN];

int new_index (int x, int y) {
    return (x - 1) * m + y;
}

bool bfs(int u) {
    queue<int> q;
    q.push(u);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < (int)graph[cur].size(); i++) {
            int v = graph[cur][i];
            if (!used[v]) {
                used[v] = true;
                if (mt[v] == -1) {
                    mt[v] = cur;
                    return true;
                }
                q.push(mt[v]);
            }
        }
    }
    return false;
}

int output() {
    int ans = 0;
    for (auto& i : mt) {
        i = -1;
    }

    for (int u = 1; u <= n * m; u++) {
        int row = (u - 1) / m + 1;
        int col;
        if (u % m == 0) {
            col = m;
        } else {
            col = u % m;
        }

        if (!visited[row][col]) {
            for (auto& i : used) {
                i = false;
            }
            if (bfs(u)) {
                ans++;
            }
        }
    }

    return ans;
}

int main () {
    cin >> n >> m >> q;

    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        visited[x][y] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!visited[i][j] && j + 1 <= m && !visited[i][j + 1]) {
                graph[new_index(i, j)].push_back (new_index(i, j + 1));
                graph[new_index(i, j + 1)].push_back (new_index(i, j));
            }

            if (!visited[i][j] && i + 1 <= n && !visited[i + 1][j]) {
                graph[new_index(i, j)].push_back (new_index(i + 1, j));
                graph[new_index(i + 1, j)].push_back (new_index(i, j));
            }
        }
    }

    cout << output() << '\n';
    return 0;
}

//#include <iostream>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//const int MAXN = 110;
//
//int n, m, q;
//bool visited[MAXN][MAXN];
//vector<int> graph[MAXN * MAXN];
//int mt[MAXN * MAXN];
//bool used[MAXN * MAXN];
//
//int new_index(int x, int y) {
//    return (x * m) + y;
//}



//bool dfs(int u) {
//    for (int i = 0; i < (int) graph[u].size(); i++) {
//        int v = graph[u][i];
//        if (!used[v]) {
//            used[v] = 1;
//            if (mt[v] == -1 || dfs(mt[v])) {
//                mt[v] = u;
//                return true;
//            }
//        }
//    }
//    return false;
//}
//
//int output() {
//    int ans = 0;
//    for (int i = 0; i <= (n * m); i++) {
//        mt[i] = -1;
//    }
//    for (int u = 0; u < (n * m); u++) {
//        if (!visited[u / m][u % m]) {
//            for (int i = 0; i <= (n * m); i++) {
//                used[i] = 0;
//            }
//            if (dfs(u)) {
//                ans++;
//            }
//        }
//    }
//
//    return ans;
//}
//
//int main() {
//    cin >> n >> m >> q;
//
//    for (int i = 0; i < q; i++) {
//        int x, y;
//        cin >> x >> y;
//        --x;
//        --y;
//        visited[x][y] = true;
//    }
//
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            if (!visited[i][j] && j + 1 < m && !visited[i][j + 1]) {
//                graph[new_index(i, j)].push_back(new_index(i, j + 1));
//                graph[new_index(i, j + 1)].push_back(new_index(i, j));
//            }
//
//            if (!visited[i][j] && i + 1 < n && !visited[i + 1][j]) {
//                graph[new_index(i, j)].push_back(new_index(i + 1, j));
//                graph[new_index(i + 1, j)].push_back(new_index(i, j));
//            }
//        }
//    }
//
//    cout << output() << '\n';
//    return 0;
//}