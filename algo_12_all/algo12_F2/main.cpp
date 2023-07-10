#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class MST {
public:
    const int INF = 1000000000;
    static const int MAX_N = 100;

    vector<vector<pair<int,int>>> adjacency_list;
    vector<bool> visited;
    vector<int> dist;

    MST() {
        adjacency_list.resize(MAX_N); // добавляем инициализацию размера
        visited.resize(MAX_N);
        dist.resize(MAX_N);
    }

    void create_adj(int a, int b, int c) {
        adjacency_list[a].emplace_back(b, c);
        adjacency_list[b].emplace_back(a, c);
    }

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
};

int main() {
    int n, m;
    cin >> n >> m;

    MST mst;
    mst.adjacency_list.resize(n);
    mst.visited.resize(n);
    mst.dist.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a;
        --b;
        mst.create_adj(a, b, c);
    }

    MST new_mst;
    new_mst.adjacency_list.resize(n);
    new_mst.visited.resize(n);
    new_mst.dist.resize(n);

    // перебираем ребра оригинального MST
    for (int i = 0; i < s1.size(); i++) {
        int v = s1[i];
        for (int j = 0; j < mst.adjacency_list[v].size(); j++) {
            int to1 = mst.adjacency_list[v][j].first;
            int weight_1 = mst.adjacency_list[v][j].second;
            if (to1 == v || weight_1 == mst.INF) {
                continue;
            }

            // удаляем i-е ребро из MST
            mst.adjacency_list[v][j].second = mst.INF;
            for (int k = 0; k < mst.adjacency_list[to1].size(); k++) {
                if (mst.adjacency_list[to1][k].first == v) {
                    mst.adjacency_list[to1][k].second = mst.INF;
                    break;
                }
            }

            // запускаем поиск минимального остовного дерева
            vector<int> s2 = new_mst.prim(0);

            // восстанавливаем удалённое ребро
            mst.adjacency_list[v][j].second = weight_1;
            for (int k = 0; k < mst.adjacency_list[to1].size(); k++) {
                if (mst.adjacency_list[to1][k].first == v) {
                    mst.adjacency_list[to1][k].second = weight_1;
                    break;
                }
            }

            // проверяем, что остовное дерево было построено со всеми вершинами
            if (s2.size() == n) {
                int cost2 = 0;
                for (int i = 0; i < s2.size(); i++) {
                    int v2 = s2[i];
                    for (int j = 0; j < new_mst.adjacency_list[v2].size(); j++) {
                        int to2 = new_mst.adjacency_list[v2][j].first;
                        int weight_2 = new_mst.adjacency_list[v2][j].second;
                        if (new_mst.visited[to2] && weight_2 != new_mst.INF) {
                            cost2 += weight_2;
                        }
                    }
                }

                // если стоимости нового MST меньше, то обновляем её
                if (cost2 < cost1) {
                    mst = new_mst;
                    cost1 = cost2;
                }
            }
        }
    }


    cout << cost1 << " " << cost2 << '\n';
    return 0;
}