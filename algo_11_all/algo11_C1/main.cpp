#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

vector<Edge> edges;
vector<vector<int>> adjacency_list;
const int INF = INT_MAX;
vector<int> dist;

bool bellman_ford(int s, int n) {

    vector<int> counter(n, 0);
    vector<bool> visited(n, false);
    dist.resize(n, INF);

    dist[s] = 0;
    visited[s] = true;

    for (int i = 0; i < n - 1; i++) { // fixed
        for (auto e : edges) {
            if (dist[e.source] < INF && dist[e.source] + e.weight < dist[e.destination]) {
                dist[e.destination] = dist[e.source] + e.weight;
                counter[e.destination] = counter[e.source] + 1;
                visited[e.destination] = true;
            }
        }
    }

    queue<int> q;

    for (int i = 0; i < n; i++) { // fixed
        for (auto e : adjacency_list[i]) {
            q.push(e);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (counter[u] > n) {
            return true;
        }
        for (int e : adjacency_list[edges[u].destination]) {
            if (dist[edges[u].destination] < INF && dist[edges[u].source] + edges[u].weight < dist[edges[e].destination]) {
                dist[edges[e].destination] = dist[edges[u].source] + edges[u].weight;
                counter[edges[e].destination] = counter[edges[u].source] + 1;
                visited[edges[e].destination] = true;
                q.push(e);
            }
        }
    }

    return false;
}

int main() {
    int N, k;
    cin >> N >> k;

    int n, m;
    int start, end, weight;
    for (int i = 0; i < N; i++) {
        cin >> n >> m;
        adjacency_list.clear();
        edges.clear();
        adjacency_list.resize(n, vector<int>());

        for (int j = 0; j < m; j++) {
            cin >> start >> end >> weight;
            --start;
            --end;
            edges.push_back({start, end, weight});
            adjacency_list[start].push_back(edges.size() - 1);
        }

        bool negative_cycle = bellman_ford(0, n);

        if (negative_cycle || dist[n - 1] > k) {
            cout << "NO" << '\n';
        } else {
            cout << "YES" << '\n';
        }
    }

    return 0;
}