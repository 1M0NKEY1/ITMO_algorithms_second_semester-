#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 2000000000;

vector<pair<int, pair<int, int>>> prim(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

    if (grid[0][0]) {
        dist[0][0] = INF;
    } else {
        dist[0][0] = 0;
    }

    pq.push({ dist[0][0], { 0, 0 } });

    vector<pair<int, pair<int, int>>> mst;

    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();

        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;

        int new_dist;
        if (x > 0 && !visited[x - 1][y]) {
            if (grid[x - 1][y]) {
                new_dist = INF;
            } else {
                new_dist = 1;
            }

            if (new_dist < dist[x - 1][y]) {
                dist[x - 1][y] = new_dist;
                pq.push({ dist[x - 1][y], { x - 1, y } });
                mst.push_back({ new_dist, { x - 1, y } });
            }
        }

        if (x < n - 1 && !visited[x + 1][y]) {
            if (grid[x][y] != 0) {
                new_dist = INF;
            } else {
                new_dist = 1;
            }

            if (new_dist < dist[x + 1][y]) {
                dist[x + 1][y] = new_dist;
                pq.push({ dist[x + 1][y], { x + 1, y } });
                mst.push_back({ new_dist, { x + 1, y } });
            }
        }

        if (y > 0 && !visited[x][y - 1]) {
            if (grid[x][y - 1]) {
                new_dist = INF;
            } else {
                new_dist = 1;
            }

            if (new_dist < dist[x][y - 1]) {
                dist[x][y - 1] = new_dist;
                pq.push({ dist[x][y - 1], { x, y - 1 } });
                mst.push_back({ new_dist, { x, y - 1 } });
            }
        }

        if (y < m - 1 && !visited[x][y + 1]) {
            if (grid[x][y]) {
                new_dist = INF;
            } else {
                new_dist = 1;
            }

            if (new_dist < dist[x][y + 1]) {
                dist[x][y + 1] = new_dist;
                pq.push({ dist[x][y + 1], { x, y + 1 } });
                mst.push_back({ new_dist, { x, y + 1 } });
            }
        }
    }

    return mst;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m;
    cin >> q;

    vector<vector<int>> grid(n, vector<int>(m, 0));

    int x, y;
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        --x;
        --y;
        grid[x][y] = 1;
    }

    auto mst = prim(grid);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 0) {
                ++ans;
            }
        }
    }

    for (auto edge : mst) {
        ans -= edge.first;
    }

    cout << ans << '\n';

    return 0;
}