#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000;
const int INF = 1e9;


vector<pair<int, int>> g[MAXN];
int d[MAXN];

void dijkstra(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, s);

    while (!pq.empty()) {
        int dist = pq.top().first;
        int v = pq.top().second;

        pq.pop();
        if (d[v] < dist)
            continue;

        for (auto u : g[v]) {
            if (d[u.first] > dist + u.second) {
                d[u.first] = dist + u.second;
                pq.emplace(d[u.first], u.first);
            }
        }
    }
}

int main() {

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        d[i] = INF;
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        --u;
        --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    dijkstra(3);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, d[i]);
    }

    cout << ans << '\n';

    return 0;
}