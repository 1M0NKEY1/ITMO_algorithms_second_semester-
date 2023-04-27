#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int source, destination;
};

class Graph {
public:
    vector<vector<int>> adjacency_list;

    Graph(vector<Edge> const &edges, int n) {
        adjacency_list.resize(n);
        for (auto &edge: edges) {
            adjacency_list[edge.source].push_back(edge.destination);
            adjacency_list[edge.destination].push_back(edge.source);
        }
    }
};

bool DFS(Graph const &graph, int v, vector<bool> &discovered, int parent) {
    discovered[v] = true;

    for (int w: graph.adjacency_list[v]) {
        if (!discovered[w]) {
            if (DFS(graph, w, discovered, v)) {
                return true;
            }
        } else if (w != parent) {
            return true;
        }
    }
    discovered[v] = false;
    return false;
}

int main() {
    vector<Edge> edges;

    int n, m;
    cin >> n >> m;
    int u, v;

    Graph graph(edges, n);

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--;
        v--;
        graph.adjacency_list[u].push_back(v);
        graph.adjacency_list[v].push_back(u);
    }

    vector<bool> discovered(n, false);

    bool check_cycle = false;
    for (int i = 0; i < n; i++) {
        if (DFS(graph, i, discovered, -1)) {
            check_cycle = true;
            break;
        }
    }
    if (check_cycle) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }

    return 0;
}