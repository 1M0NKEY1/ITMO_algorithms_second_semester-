#include <iostream>
#include <list>
#include <stack>
#include <vector>
using namespace std;


class Graph {
private:
    int V;
    list<int>* adjacency_list;

    void top_sort_util(int v, vector<bool> visited) {
        visited[v] = true;
        
        for (auto i: adjacency_list[v])
            if (!visited[i])
                top_sort_util(i, visited);


        Stack.push(v);
    }

public:
    Graph(int V) {
        this->V = V;
        adjacency_list = new list<int>[V];
    }

    stack<int> Stack;

    void add_edge(int v, int w) {
        adjacency_list[v].push_back(w);
    }

    void top_sort() {
        vector<bool> visited(adjacency_list->size(), false);

        for (int i = 0; i < V; i++)
            if (!visited[i])
                top_sort_util(i, visited);

        while (!Stack.empty()) {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }

};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    Graph g(n);

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        g.add_edge(a, b);
    }

    g.top_sort();

    return 0;
}
