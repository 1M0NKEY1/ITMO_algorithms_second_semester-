#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 110;

int n, m, q;
bool a[MAXN][MAXN];
vector<int> g[MAXN * MAXN];
bool visited[MAXN * MAXN];
int mt[MAXN * MAXN];

bool kuhn_algorithm(int v) {
    if (visited[v]) {
        return false;
    }
    visited[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (mt[to] == -1 || (!visited[mt[to]] && kuhn_algorithm(mt[to]))) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m >> q;
    memset(a, false, sizeof(a));
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        a[x - 1][y - 1] = true;
    }

    for (int i = 0; i < n * m; i++) {
        g[i].clear();
    }

    int last_row_start = (n - 1) * m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = i * m + j;
            int v = i * m + (j + 1) % m;
            if (j < m - 1 && !a[i][j] && !a[i][j+1]) {
                g[u].push_back(v + n);
                g[v + n].push_back(u);
            }
            v = ((i + 1) % n) * m + j;
            if (i < n - 1 && !a[i][j] && !a[i+1][j]) {
                g[u].push_back(v + n);
                g[v + n].push_back(u);
            }
        }
    }

    memset(mt, -1, sizeof(mt));
    int start_v = 0;
    int ans = 0;
    for (int v = start_v; v < last_row_start; v++) {
        memset(visited, false, sizeof(visited));
        if (kuhn_algorithm(v)) {
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}