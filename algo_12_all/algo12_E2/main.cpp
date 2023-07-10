#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;
int n, m;
vector<vector<int>> cap, flow;
vector<int> parent;

bool bfs(int s, int t) {
    vector<bool> visited(n, false);
    visited[s] = true;
    parent[s] = -1;

    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (!visited[v] && cap[u][v] - flow[u][v] > 0) {
                visited[v] = true;
                q.push(v);
                parent[v] = u;
            }
        }
    }

    return visited[t];
}

int Flow(int s, int t) {
    int max_flow = 0;

    while (bfs(s, t)) {
        int path_flow = INF;
        for (int u = t; u != s; u = parent[u]) {
            int prev = parent[u];
            path_flow = min(path_flow, cap[prev][u] - flow[prev][u]);
        }

        for (int u = t; u != s; u = parent[u]) {
            int prev = parent[u];
            flow[prev][u] += path_flow;
            flow[u][prev] -= path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {
    cin >> n >> m;

    cap.assign(n, vector<int>(n, 0));
    flow.assign(n, vector<int>(n, 0));
    parent.assign(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        cap[u][v] += w;
    }

    cout << Flow(0, n - 1) << '\n';

    return 0;
}