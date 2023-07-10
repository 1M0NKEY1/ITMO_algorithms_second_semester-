#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN = 10010, MAXM = 10010;
int n, m, q, match[MAXN], vis[MAXN], head[MAXN], tot;
struct edge { int to, next; } e[MAXM];
vector<int> G[MAXN];

void add_edge(int u, int v) {
    e[++tot].to = v;
    e[tot].next = head[u];
    head[u] = tot;
}

bool dfs(int u) {
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!vis[v]) {
            vis[v] = true;
            if (!match[v] || dfs(match[v])) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

int max_match() {
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if (dfs(i)) ans++;
    }
    return ans;
}

int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= q; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id1 = (i - 1) * m + j, id2 = id1 + n * m;
            for (int k = 0; k < G[i].size(); k++) {
                int y = G[i][k];
                if (j == y || j + 1 == y) break;
                if (j < y) add_edge(id1, id2 - m + y - 1);
                else add_edge(id1, id2 + y - 1);
            }
            if (i < n) add_edge(id1, id2 + m);
        }
    }

    cout << max_match() << endl;
    return 0;
}