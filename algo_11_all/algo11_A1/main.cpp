#include <iostream>
#include <vector>
#include <queue>
#include <list>

using namespace std;

struct Edge {
    int source;
    int destination;
    int weight;
};

class Graph {
private:
    int V;
    list<pair<int, int>> *adjacency_list;
public:
    Graph(int v) {
        this->V = v;
        adjacency_list = new list<pair<int, int>>[v];
    }

    void add_edge(int u, int v, int w) {
        adjacency_list[u].emplace_back(v, w);
        adjacency_list[v].emplace_back(u, w);
    }

    void dijkstra(int source) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        vector<int> dist(V, INT_MAX);

        pq.push(make_pair(0, source));
        dist[source] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            list<pair<int, int>>::iterator i;
            for (i = adjacency_list[u].begin(); i != adjacency_list[u].end(); i++) {
                int v = (*i).first;
                int weight = (*i).second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        for (int i = 0; i < V; ++i) {
            cout << i << "\t\t" << dist[i] << "\n";
        }
    }
};

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    Graph graph(n);
    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graph.add_edge(u, v, w);
    }

    graph.dijkstra(0);

    return 0;
}
