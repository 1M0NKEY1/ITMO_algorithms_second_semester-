#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> adjacency_list;

void add_edge(int u, int v) {
    adjacency_list[u].push_back(v);
    adjacency_list[v].push_back(u);
}

void delete_edge(int u, int v) {
    for (int i = 0; i < adjacency_list[u].size(); i++) {
        if (adjacency_list[u][i] == v) {
            adjacency_list[u].erase(adjacency_list[u].begin() + i);
            break;
        }
    }
    for (int i = 0; i < adjacency_list[v].size(); i++) {
        if (adjacency_list[v][i] == u) {
            adjacency_list[v].erase(adjacency_list[v].begin() + i);
            break;
        }
    }
}

bool check(int a, int b) {
    if (a == b) {
        return true;
    }
    int n = (int)adjacency_list.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[a] = true;
    q.push(a);
    while (!q.empty()) {
        a = q.front();
        q.pop();
        for (int i: adjacency_list[a]) {
            if (i == b) {
                return true;
            }
            if (!visited[i]) {
                visited[i];
                q.push(i);
            }
        }
    }
    return false;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    adjacency_list = vector<vector<int>>(n);

    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        add_edge(a, b);
    }

    char symbol;
    int checked_a, checked_b;
    for (int i = 0; i < q; i++) {
        cin >> symbol >> checked_a >> checked_b;
        if (symbol == '?') {
            if (check(checked_a, checked_b)) {
                cout << "YES" << '\n';
            } else {
                cout << "NO" << '\n';
            }
        } else if (symbol == '-') {
            delete_edge(checked_a, checked_b);
        }
    }


    return 0;
}
