#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000;
const int INF = 1000000000;

vector<pair<int, int>> adjacency_list[MAXN];

int prim() {
    vector<int> dist(MAXN, INF);
    vector<bool> visited(MAXN, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.emplace(0, 0);
    int ans = 0;
    dist[0] = 0;

    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        ans += d;

        for (auto v: adjacency_list[u]) {
            int w = v.second;
            if (w < dist[v.first] && !visited[v.first]) {
                dist[v.first] = w;
                pq.emplace(w, v.first);
            }
        }
    }

    return ans;
}

int main() {

    int n, m;
    cin >> n >> m;

    int u, v, w;
    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u;
        --v;
        adjacency_list[u].emplace_back(v, w);
        adjacency_list[v].emplace_back(u, w);
    }

    cout << prim() << '\n';

    return 0;
}