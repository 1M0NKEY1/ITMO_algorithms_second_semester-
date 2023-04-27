#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Структура данных для хранения ребра Graph
struct Edge {
    int src, dest;
};

// Класс для представления graphического объекта
class Graph
{
public:

    // вектор векторов для представления списка смежности
    vector<vector<int>> adjList;

    // Конструктор Graphа
    Graph(vector<Edge> const &edges, int n)
    {
        // изменить размер вектора, чтобы он содержал `n` элементов типа `vector<int>`
        adjList.resize(n);

        // добавляем ребра в неориентированный graph
        for (auto &edge: edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

// Выполняем поиск в глубину на Graph и возвращаем true, если на Graph найдено какое-либо обратное ребро
bool DFS(Graph const &graph, int v, vector<bool> &discovered, int parent)
{
    // помечаем текущий узел как обнаруженный
    discovered[v] = true;

    // делаем для каждого ребра (v, w)
    for (int w: graph.adjList[v])
    {
        // если `w` не обнаружен
        if (!discovered[w])
        {
            if (DFS(graph, w, discovered, v)) {
                return true;
            }
        }

        // если `w` обнаружен, а `w` не является родителем
        else if (w != parent)
        {
            // мы нашли обратное ребро (цикл)
            return true;
        }
    }

    // Обратных ребер на Graphе не обнаружено
    return false;
}

int main()
{
    // инициализируем ребра
    vector<Edge> edges = { {1, 2}, {1, 3}, {2, 3} };

    // общее количество узлов в Graph (от 0 до 11)
    int n = 3;

    // строим graph из заданных ребер
    Graph graph(edges, n);

    // чтобы отслеживать, открыта вершина или нет
    vector<bool> discovered(n);

    // Выполняем обход в глубину из первой вершины
    if (DFS(graph, 1, discovered, 0)) {
        cout << "The graph contains a cycle";
    }
    else {
        cout << "The graph doesn't contain any cycle";
    }

    return 0;
}