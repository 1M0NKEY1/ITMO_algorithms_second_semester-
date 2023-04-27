#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int source, destination;
};

class Graph {
public:
    vector<vector<int>> adjacency_list;
    vector<int> answers;
    int counter;

    Graph(vector<Edge> const &edges, int n) {
        adjacency_list.resize(n);
        for (auto &edge: edges) {
            adjacency_list[edge.source].push_back(edge.destination);
        }
    }

    bool DFS(int v, vector<int> &discovered, int n) {
        discovered[v] = 1;
        answers.resize(n);

        for (int w: adjacency_list[v]) {
            if (discovered[w] == 0) {
                if (DFS(w, discovered, n)) {
                    return true;
                }
            }
        }

        counter--;
        answers[v] = counter;
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
    graph.counter = n;

    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--;
        v--;
        graph.adjacency_list[u].push_back(v);
    }

    for (int i = 0; i < n; i++) {
        if (discovered[i] == 0) {
            graph.DFS(i, discovered, n);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << graph.answers[i] + 1 << ' ';
    }

    return 0;
}
