#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_vertices, num_edges;
vector<vector<int>> edges;
vector<bool> visited;
vector<vector<int>> residual_network;

int Flow(int source, int sink, int minimum) {
    visited[source] = true;
    if (source == sink) {
        return minimum;
    }
    for (int i = 0; i < num_vertices; i++) {
        int flow_capacity = edges[source][i] - residual_network[source][i];
        if (!visited[i] && flow_capacity > 0) {
            if (int sent = Flow(i, sink, min(minimum, flow_capacity))) {
                residual_network[source][i] += sent;
                residual_network[i][source] -= sent;
                return sent;
            }
        }
    }
    return 0;
}

int main() {
    cin >> num_vertices >> num_edges;
    edges.resize(num_vertices);
    residual_network.resize(num_vertices);

    for (int i = 0; i < num_vertices; i++){
        edges[i].resize(num_vertices);
        residual_network[i].resize(num_vertices);
    }

    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            edges[i][j] = 0;
            residual_network[i][j] = 0;
        }
    }

    for (int i = 0; i < num_edges; i++) {
        int v_to, v_from, v_bandwidth;
        cin  >> v_from >> v_to>> v_bandwidth;
        v_to--;
        v_from--;

        edges[v_from][v_to] = v_bandwidth;
        v_bandwidth = 0;
        residual_network[v_to][v_from] = v_bandwidth;
    }

    visited.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++) {
        visited[i] = false;
    }

    int K = 0;
    int iteration;
    while ((iteration = Flow(0, num_vertices - 1, 1e9)) > 0) {
        for (int k = 0; k < num_vertices; k++) {
            visited[k] = false;
        }
        K += iteration;
    }

    cout << K;

    return 0;
}