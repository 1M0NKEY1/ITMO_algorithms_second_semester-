#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

vector<int> parent;
vector<int> Rank;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (Rank[a] < Rank[b])
            swap(a, b);
        parent[b] = a;
        if (Rank[a] == Rank[b])
            Rank[a]++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, pair<int, int>>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        edges[i] = make_pair(c, make_pair(a - 1, b - 1)); // сохраняем соединение с учетом нумерации с 0
    }

    // Сортируем ребра по возрастанию стоимости
    sort(edges.begin(), edges.end());

    vector<int> ans;
    for (int k = 0; k < 2; k++) { // запускаем цикл дважды (для нахождения двух минимальных стоимостей)
        int min_cost = INF;

        // Инициализируем наборы и ранги
        parent.resize(n);
        Rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            Rank[i] = 0;
        }

        // Проходим по всем ребрам в порядке возрастания стоимости
        for (auto edge : edges) {
            int w = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            if (find_set(u) != find_set(v)) {
                union_sets(u, v);
                min_cost = min(min_cost, w);
            }
        }

        // Если находимся в первом запуске, добавляем найденную минимальную стоимость в ответ
        // Если во втором - добавляем, если она отличается от первой
        if (k == 0)
            ans.push_back(min_cost);
        else if (min_cost != ans[0])
            ans.push_back(min_cost);
    }

    // Выводим две минимальные стоимости
    for (int cost : ans)
        cout << cost << " ";
    cout << endl;

    return 0;
}