//#include <iostream>
//#include <vector>
//#include <queue>
//#include <list>
//
//
//using namespace std;
//
//class Graph {
//private:
//    int V;
//    list<pair<int, int>> *adjacency_list;
//public:
//    Graph(int V) {
//        this->V = V;
//        adjacency_list = new list<pair<int, int>>[V];
//    }
//
//    void addEdge(int u, int v, int w) {
//        adjacency_list[u].emplace_back(v, w);
//        adjacency_list[v].emplace_back(u, w);
//    }
//
//    void Dijkstra(int src, int dst) {
//        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
//        vector<int> dist(V, 2000000000);
//        vector<bool> visited(V, false);
//
//        pq.emplace(0, src);
//        dist[src] = 0;
//
//        while (!pq.empty()) {
//            int u = pq.top().second;
//            pq.pop();
//
//            if (visited[u]) {
//                continue;
//            }
//            visited[u] = true;
//
//            for (auto i : adjacency_list[u]) {
//                int v = i.first;
//                int weight = i.second;
//
//                if (dist[v] > dist[u] + weight) {
//                    dist[v] = dist[u] + weight;
//                    pq.emplace(dist[v], v);
//                }
//            }
//        }
//
//        if (dist[dst] > 1000000 || dist[dst] < 0) {
//            cout << -1 << '\n';
//        } else {
//            cout << dist[dst] << '\n';
//        }
//    }
//};
//
//
//int main() {
//    ios::sync_with_stdio(0);
//    cin.tie(0);
//
//    int n, m, q, start;
//    cin >> n >> m >> q >> start;
//
//    Graph graph(n);
//
//    int source, destination, weight;
//    for (int i = 0; i < m; i++) {
//        cin >> source >> destination >> weight;
//        --source;
//        --destination;
//        graph.addEdge(source, destination, weight);
//    }
//
//    int end;
//    --start;
//    for (int i = 0; i < q; i++) {
//        cin >> end;
//        --end;
//        graph.Dijkstra(start, end);
//    }
//
//    return 0;
//}
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = INT_MAX;
vector<vector<pair<int,int>>> graph;
vector<int> dist;

void dijkstra(int start) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.emplace(dist[start], start);

    while (!pq.empty()) {
        int v = pq.top().second;
        int d_v = pq.top().first;
        pq.pop();

        if (d_v != dist[v])
            continue;

        for (auto edge : graph[v]) {
            int to = edge.first;
            int len = edge.second;
            if (dist[v] + len < dist[to]) {
                dist[to] = dist[v] + len;
                pq.emplace(dist[to], to);
            }
        }
    }
}

int main() {
    int n, m, q, start;
    cin >> n >> m >> q >> start;
    graph.resize(n);
    dist.assign(n, INF);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u;
        --v;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    --start;
    dijkstra(start);

    int dest;
    for (int j = 0; j < q; j++) {
        cin >> dest;
        --dest;
        if (dist[dest] == INF)
            cout << "-1" << '\n';
        else
            cout << dist[dest] << '\n';
    }

    return 0;
}