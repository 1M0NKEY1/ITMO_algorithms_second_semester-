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
};


struct way_visited {
    int way;
    bool visited;
    way_visited() {
        way = 0;
        visited = false;
    }
};

int N;

bool DFS(Graph const &graph, int current_vertex, vector<bool> &discovered,int counter) {
    discovered[current_vertex] = true;
    ++counter;

    if (counter == N) {
        return true;
    }

    for (int w : graph.adjacency_list[current_vertex]) {
        if (!discovered[w]) {
            if (DFS(graph, w, discovered, counter)) {
                return true;
            }
        }
    }

    discovered[current_vertex] = false;
    return false;
}


int main() {
    vector<Edge> edges;
    queue<int> q;


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

    int start = 0;
    vector<way_visited> info(n);
    vector<int> depth(n, -1);
    depth[start] = 0;
    info[start].visited = true;
    q.push(start);
    int last_vertex = start;

    while (!q.empty()) {
        int number = q.front();
        q.pop();
        for (int i = 0; i < graph.adjacency_list[number].size(); i++) {
            int vertex = graph.adjacency_list[number][i];
            if (!info[vertex].visited) {
                info[vertex].visited = true;
                depth[vertex] = depth[number] + 1;
                if (depth[vertex] > depth[last_vertex]) {
                    last_vertex = vertex;
                }
                q.push(vertex);
            }
        }
    }

    N = n;

    if (DFS(graph, last_vertex, discovered, 0)) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }


    return 0;
}
