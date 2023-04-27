#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> P;
priority_queue<P, vector<P>, greater<P>> q;

const int inf = 1000000000, N = 1010, M = 100010, K = 22;

int h[N], cnt = 0;

struct qwq {
    int source, destination, weight;
} adjacency_list[M << 1];

inline void add(int u,int v, int w) { // Функция для добавления ребра в список смежности
    adjacency_list[++cnt].source = v;
    adjacency_list[cnt].destination = h[u];
    adjacency_list[cnt].weight = w;
    h[u] = cnt;
}

int distants[K + 10][N];
int visited[N];

int dijkstra(int s,int e) {
    memset(distants, 127, sizeof(distants)); // Заполняем массив бесконечными значениями
    memset(visited, 0, sizeof(visited));

    while(q.size())
        q.pop();

    distants[0][s] = 0; // Установка стартовых значений расстояния
    q.push(make_pair(0,s));

    while(q.size()) {
        P p = q.top();
        q.pop();
        int x = p.second;
        if(visited[x])
            continue;
        visited[x] = 1;

        for(int i = h[x]; i; i = adjacency_list[i].destination) {
            int v = adjacency_list[i].source;
            int w = adjacency_list[i].weight;
            int tmp = -1;
            if (i % 2 == 0)
                continue;
            if (i % 2 == 1 && distants[p.first][x] <= distants[p.first][x + 1] - w && x + 1 <= K) { // Определяем, какая третья вершина соседней вершины (при перемещении вперед)
                tmp = x + 1;
                if (distants[tmp][v] > distants[p.first][x] + w) {
                    distants[tmp][v] = distants[p.first][x] + w;
                    q.push(make_pair(distants[tmp][v], v));
                }
            } else if (i % 2 == 1 && distants[p.first][x] >= distants[p.first][x + 1] + w && x - 1 >= 0) {// Определяем, какая третья вершина соседней вершины (при перемещении назад)
                tmp = x - 1;
                if(distants[tmp][v] > distants[p.first][x] + w) {
                    distants[tmp][v]= distants[p.first][x] + w;
                    q.push(make_pair(distants[tmp][v], v));
                }
            }
        }
    }

    int ans = inf;
    for(int i = 0; i <= K; i++)
        ans = min(ans, distants[i][e]);
    if(ans == distants[K + 1][0])
        return -1;
    else
        return ans;
}

int main() {
    int n, m, s, e, u, v, w;

    memset(h,0,sizeof(h));
    cnt = 1;
    int k;
    cin >> n >> m >> k;

    for(int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        ++u,++v;
        add(u, v, w);
        add(v,u, w + k);
        add(u, v + k, w + k);
        add(v, u + k, w);
    }

    for (int i = 0; i < 4; i++) {
        cin >> s >> e;
        ++s;
        ++e;
        cout << dijkstra(s,e) << '\n';
    }

    return 0;
}
