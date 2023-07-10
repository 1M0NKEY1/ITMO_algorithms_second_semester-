#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000;
const int INF = 200000000;

int N, M;
vector<pair<int,int>> adjacency_list[MAXN];
vector<bool> visited;
vector<int> dist;
vector<int> parent;
int cap[MAXN][MAXN];


void prim(){
    dist.resize(MAXN, INF);
    visited.resize(MAXN, false);
    parent.resize(MAXN, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;

    dist[0] = 0;
    pq.emplace(0,0);

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for(auto v: adjacency_list[u]){
            if(!visited[v.first] && dist[v.first] > v.second){
                dist[v.first] = v.second;
                pq.emplace(dist[v.first], v.first);
                parent[v.first] = u;
            }
        }
    }
}

int max_flow(){
    int ans = 0;
    while(true){
        prim();

        if(dist[N - 1] == INF)
            break;

        int flow = INF;
        for(int i = N - 1; i != 0; i = parent[i]){
            flow = min(flow, cap[parent[i]][i]);
        }

        ans += flow;

        for(int i = N - 1; i != 0; i = parent[i]){
            int u = parent[i], v = i;
            cap[u][v] -= flow;
            cap[v][u] += flow;
        }
    }

    return ans;
}

int main(){
    cin >> N >> M;

    int u, v, c;
    for(int i = 0; i < M; i++){
        cin >> u >> v >> c;
        --u;
        --v;

        adjacency_list[u].emplace_back(v, c);
        adjacency_list[v].emplace_back(u, c);

        cap[u][v] += c;
        cap[v][u] += c;
    }

    cout << max_flow() << '\n';

    return 0;
}