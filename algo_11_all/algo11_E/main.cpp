#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = INT_MAX;
vector<vector<pair<int, int>>> adjacency_list;

void dijkstra(int n, int start, int end) {
    vector<int> dist(n, INF);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int d = pq.top().first;
        int v = pq.top().second;
        pq.pop();

        if (d > dist[v]) {
            continue;
        }

        for (auto e : adjacency_list[v]) {
            int u = e.first;
            int w = e.second;

            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                pq.emplace(dist[u], u);
            }
        }
    }

    if (dist[end] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dist[end] << '\n';
    }
}

int main() {
    int n, m, start, end;
    cin >> n >> m;
    cin >> start >> end;

    adjacency_list.resize(n);

    int source, destination, weight;
    for (int i = 0; i < m; ++i) {
        cin >> source >> destination >> weight;
        --source;
        --destination;
        adjacency_list[source].emplace_back(destination, weight);
    }

    --start;
    --end;
    dijkstra(n, start, end);

    return 0;
}