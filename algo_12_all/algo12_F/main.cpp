#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000000;
const int MAX_N = 100;

vector<pair<int,int>> adjacency_list[MAX_N];
vector<bool> visited(MAX_N);
vector<int> dist(MAX_N);

vector<int> prim(int start) {
    vector<int> res;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.emplace(0, start);

    for (int i = 0; i < MAX_N; i++) {
        visited[i] = false;
        dist[i] = INF;
    }

    dist[start] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (auto t : adjacency_list[u]) {
            int v = t.first;
            int weight = t.second;
            if (dist[v] > weight && !visited[v]) {
                dist[v] = weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    for (int i = 0; i < MAX_N; i++) {
        if (visited[i]) {
            res.push_back(i);
        }
    }

    return res;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        adjacency_list[a].emplace_back(b, c);
        adjacency_list[b].emplace_back(a, c);
    }

    vector<int> s1 = prim(0);
    int cost1 = 0;
    for (int i = 0; i < s1.size(); i++) {
        int v = s1[i];
        for (int j = 0; j < adjacency_list[v].size(); j++) {
            int to1 = adjacency_list[v][j].first;
            int weight_1 = adjacency_list[v][j].second;

            if (visited[to1] && weight_1 != INF) {
                cost1 += weight_1;
            }
        }
    }

    vector<int> s2;
    int cost2 = INF;
    for (int i = 0; i < s1.size(); i++) {
        int v = s1[i];
        for (int j = 0; j < adjacency_list[v].size(); j++) {
            int to2 = adjacency_list[v][j].first;
            int weight_2 = adjacency_list[v][j].second;

            if (v < to2 && weight_2 != INF) {
                int original_w = weight_2;
                adjacency_list[v][j].second = INF;

                for (int k = 0; k < adjacency_list[to2].size(); k++) {
                    if (adjacency_list[to2][k].first == v) {
                        adjacency_list[to2][k].second = INF;
                        break;
                    }
                }

                vector<int> s = prim(0);
                int cost = 0;
                for (int k = 0; k < s.size(); k++) {
                    int u = s[k];
                    for (int l = 0; l < adjacency_list[u].size(); l++) {
                        int to = adjacency_list[u][l].first;
                        int weight = adjacency_list[u][l].second;
                        if (u < to && visited[u] && visited[to] && weight != INF) {
                            cost += weight;
                        }
                    }
                }

                if (cost < cost2) {
                    s2 = s;
                    cost2 = cost;
                }

                adjacency_list[v][j].second = original_w;
                for (int k = 0; k < adjacency_list[to2].size(); k++) {
                    if (adjacency_list[to2][k].first == v) {
                        adjacency_list[to2][k].second = original_w;
                        break;
                    }
                }
            }
        }
    }

    cout << cost1 << " " << cost2 << '\n';

    return 0;
}