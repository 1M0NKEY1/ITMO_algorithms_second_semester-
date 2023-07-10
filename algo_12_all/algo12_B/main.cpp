#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long MAXN = 100001;
const long INF = 2000000000;

vector<pair<long, long>> adjacency_list[MAXN];

long prim() {
    vector<long> dist(MAXN, INF);
    vector<bool> visited(MAXN, false);

    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<pair<long, long>>> pq;

    pq.emplace(0, 0);
    long ans = 0;
    dist[0] = 0;

    while(!pq.empty()) {
        long d = pq.top().first;
        long u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;

        visited[u] = true;
        ans += d;

        for (auto v: adjacency_list[u]) {
            long w = v.second;
            if (w < dist[v.first] && !visited[v.first]) {
                dist[v.first] = w;
                pq.emplace(w, v.first);
            }
        }
    }

    return ans;
}

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    long u, v, w;
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