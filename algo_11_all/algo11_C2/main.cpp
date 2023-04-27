#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

struct Edge {
    int source, destination, weight;
};

void bellman_ford(int s, int n, vector<Edge>& edges, vector<vector<int>>& adjacency_list) {
    vector<int> dist(n, INF);
    dist[s] = 0;

    vector<int> counter(n, 0);
    counter[s] = 1;

    vector<bool> visited(n, false);
    visited[s] = true;

    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        visited[v] = false;

        for (int i : adjacency_list[v]) {
            Edge& e = edges[i];
            if (dist[v] != INF && dist[e.destination] > dist[v] + e.weight) {
                dist[e.destination] = dist[v] + e.weight;
                counter[e.destination] = counter[v] + 1;
                if (!visited[e.destination]) {
                    q.push(e.destination);
                    visited[e.destination] = true;
                }
                if (counter[e.destination] >= n) {
                    cout << "NO" << '\n';
                    return;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j : adjacency_list[i]) {
            Edge& e = edges[j];
            if (dist[i] != INF && dist[e.destination] > dist[i] + e.weight) {
                cout << "NO" << '\n';
                return;
            }
        }
    }

    cout << "YES" << '\n';
}

int main() {
    int N, k;
    cin >> N >> k;
    for (int i = 0; i < N; i++) {
        int n, m;
        cin >> n >> m;
        vector<Edge> edges(m);
        vector<vector<int>> adjacency_list(n);

        int start, end, weight;
        for (int j = 0; j < m; j++) {
            cin >> start >> end >> weight;
            --start;
            --end;
            edges[j] = {start, end, weight };
            adjacency_list[start].push_back(j);
        }
        bellman_ford(0, n, edges, adjacency_list);
    }

    return 0;
}