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

struct Qnode {
    int value;
    Qnode* next;
    Qnode(int val) {
        value = val;
        next = nullptr;
    }
};

struct Queue {
    Qnode *head;
    Qnode *tail;

    Queue() { head = tail = nullptr; }

    void push(int x) {
        Qnode *tmp = new Qnode(x);
        if (tail == nullptr) {
            head = tail = tmp;
            return;
        }
        tail->next = tmp;
        tail = tmp;
    }
    void pop() {
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Qnode *tmp = head;
            head = head->next;
            delete tmp;
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
    Queue q;

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
    info[start].visited = true;

    int last_vertex = start;
    vector<int> depth(n, -1);
    depth[start] = 0;
    q.push(start);

    while (q.head != nullptr) {
        int number = q.head->value;
        q.pop();
        for (int i = 0; i < graph.adjacency_list[number].size(); i++) {
            if (!info[graph.adjacency_list[number][i]].visited) {
                info[graph.adjacency_list[number][i]].visited = true;
                info[graph.adjacency_list[number][i]].way = info[number].way + 1;
                if (info[graph.adjacency_list[number][i]].way > info[last_vertex].way) {
                    last_vertex = graph.adjacency_list[number][i];
                }
                q.push(graph.adjacency_list[number][i]);
            }
        }
    }

    if (DFS(graph, last_vertex, discovered, 0)) {
        cout << "YES" << '\n';
    } else {
        cout << "NO" << '\n';
    }


    return 0;
}