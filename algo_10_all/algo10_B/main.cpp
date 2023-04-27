#include <iostream>
#include <vector>
#include <queue>

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

    bool check(int a, int b) {
        if (a == b) {
            return true;
        }
        vector<bool> visited(adjacency_list.size(), false);
        queue<int> q;

        visited[a] = true;
        q.push(a);
        while (!q.empty()) {
            a = q.front();
            q.pop();
            for (auto i: adjacency_list[a]) {
                if (i == b) {
                    return true;
                }
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        return false;
    }

    void delete_edge(int a, int b) {
        for (int i = 0; i < adjacency_list.size(); i++) {
            if (adjacency_list[a][i] == b) {
                adjacency_list[a].erase(adjacency_list[a].begin() + i);
                break;
            }
        }

        for (int i = 0; i < adjacency_list.size(); i++) {
            if (adjacency_list[b][i] == a) {
                adjacency_list[b].erase(adjacency_list[b].begin() + i);
                break;
            }
        }
    }

};




int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    vector<Edge> edges;
    int n, m, q;
    cin >> n >> m >> q;

    Graph graph(edges, n);
    int a, b;

    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        graph.adjacency_list[a].push_back(b);
        graph.adjacency_list[b].push_back(a);
    }

    char symbol;
    int checked_a, checked_b;
    for (int i = 0; i < q; i++) {
        cin >> symbol >> checked_a >> checked_b;
        checked_a--;
        checked_b--;
        if (symbol == '?') {
            if (graph.check(checked_a, checked_b)) {
                cout << "YES" << '\n';
            } else {
                cout << "NO" << '\n';
            }
        } else if (symbol == '-') {
            graph.delete_edge(checked_a, checked_b);
        }
    }


    return 0;
}
