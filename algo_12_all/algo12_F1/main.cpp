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
        adjacency_list.resize(MAX_N);
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

    vector<int> s1 = mst.prim(0);
    int cost1 = 0;
    for (int v : s1) {
        for (int j = 0; j < mst.adjacency_list[v].size(); j++) {
            int to1 = mst.adjacency_list[v][j].first;
            int weight_1 = mst.adjacency_list[v][j].second;
            if (mst.visited[to1] && weight_1 != mst.INF) {
                cost1 += weight_1;
            }
        }
    }

    vector<int> s2;
    int cost2 = mst.INF;
    for (int i = 0; i < s1.size(); i++) {
        int v = s1[i];
        for (int j = 0; j < mst.adjacency_list[v].size(); j++) {
            int to2 = mst.adjacency_list[v][j].first;
            int weight_2 = mst.adjacency_list[v][j].second;
            if (v < to2 && weight_2 != mst.INF) {
                int original_w = weight_2;
                mst.adjacency_list[v][j].second = mst.INF;
                for (int k = 0; k < mst.adjacency_list[to2].size(); k++) {
                    if (mst.adjacency_list[to2][k].first == v) {
                        mst.adjacency_list[to2][k].second = mst.INF;
                        break;
                    }
                }
                vector<int> s = mst.prim(0);
                int cost = 0;
                for (int k = 0; k < s.size(); k++) {
                    int u = s[k];
                    for (int l = 0; l < mst.adjacency_list[u].size(); l++) {
                        int to = mst.adjacency_list[u][l].first;
                        int weight = mst.adjacency_list[u][l].second;
                        if (u < to && mst.visited[u] && mst.visited[to] && weight != mst.INF) {
                            cost += weight;
                        }
                    }
                }
                if (cost < cost2) {
                    s2 = s;
                    cost2 = cost;
                }
                mst.adjacency_list[v][j].second = original_w;
                for (int k = 0; k < mst.adjacency_list[to2].size(); k++) {
                    if (mst.adjacency_list[to2][k].first == v) {
                        mst.adjacency_list[to2][k].second = original_w;
                        break;
                    }
                }
            }
        }
    }
    cout << cost1 << " " << cost2 << '\n';
    return 0;
}