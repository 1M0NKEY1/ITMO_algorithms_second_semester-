#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int source, destination;
};

class Graph {
public:
    vector<vector<int>> adjacency_list;
    vector<int> components;

    Graph(vector<Edge> const &edges, int n) {
        adjacency_list.resize(n);
        for (auto &edge: edges) {
            adjacency_list[edge.source].push_back(edge.destination);
            adjacency_list[edge.destination].push_back(edge.source);
        }
    }

    bool DFS(int v, vector<int> &discovered, int n, int counter) {
        discovered[v] = 1;
        components.resize(n);
        components[v] = counter;

        for (int w: adjacency_list[v]) {
            if (discovered[w] == 0) {
                if (DFS(w, discovered, n, counter)) {
                    return true;
                }
            }
        }

        discovered[v] = 2;
        return false;
    }

};

int main() {
    vector<Edge> edges;

    int n, m;
    cin >> n >> m;

    Graph graph(edges, n);
    vector<int> discovered(n, 0);
    int counter = 0;

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--;
        v--;
        graph.adjacency_list[u].push_back(v);
        graph.adjacency_list[v].push_back(u);
    }

    vector<int> rooms(n);
    for (int i = 0; i < n; i++) {
        cin >> rooms[i];
    }

    for (int i = 0; i < n; i++) {
        if (discovered[i] == 0) {
            graph.DFS(i, discovered, n, ++counter);
        }
    }

    vector<int> result(counter, 0);
    int point;
    for (int i = 0; i < n; i++) {
        if (rooms[i] == 1) {
            point = graph.components[i];
            point--;
            result[point] = 1;
        }
    }

    cout << counter << '\n';
    for (int i = 0; i < n; i++) {
        cout << graph.components[i] << ' ';
    }
    cout << '\n';
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << ' ';
    }

    return 0;
}
