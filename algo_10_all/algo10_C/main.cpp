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
        }
    }

    bool check(int a, int b) {
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
    }

    int checked_a, checked_b;
    for (int i = 0; i < q; i++) {
        cin >> checked_a >> checked_b;
        checked_a--;
        checked_b--;
        if (graph.check(checked_a, checked_b) and graph.check(checked_b, checked_a)) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}
