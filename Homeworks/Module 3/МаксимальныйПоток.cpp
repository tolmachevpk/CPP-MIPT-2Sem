#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

class CGraph {
public:
    CGraph(int n) {
        g.assign(n + 1, vector<int>(n + 1, 0));
    }

    void add(int a, int b, int w) {
        g[a][b] = w;    }

    vector<vector<int>> getGraph() {
        return g;
    }

private:
    vector<vector<int>> g;
};

vector<int> bfs(int start, int end, vector<vector<int>> graph) {
    vector<int> used(graph.size(), false);
    vector<int> parent(graph.size());
    parent[start] = -1;
    used[start] = true;
    queue<int> q;
    q.push(start);
    while (!q.empty() && !used[end]) {
        int u = q.front();
        q.pop();
        for (int i = 1; i < graph.size(); i++) {
            if (graph[u][i] > 0 && !used[i]) {
                parent[i] = u;
                used[i] = true;
                q.push(i);
            }
        }
    }
    vector<int> result;
    if(used[end]) {
        int cur = end;
        while(cur != start) {
            result.push_back(cur);
            cur = parent[cur];
        }
        reverse(result.begin(), result.end());
        return result;
    }
    return result;
}

int edmKarp(int start, int end, vector<vector<int>> graph) {
    vector<int> minWay = bfs(start, end, graph);
    int maxFlow = 0;
    while(minWay.size() != 0) {
        int minFlow = INF;
        int cur = start;
        for(int i = 0; i < minWay.size(); i++) {
            if(graph[cur][minWay[i]] < minFlow) {
                minFlow = graph[cur][minWay[i]];
            }
            cur = minWay[i];
        }
        maxFlow += minFlow;
        graph[start][minWay[0]] -= minFlow;
        graph[minWay[0]][start] += minFlow;
        for (int i = 0; i < minWay.size() - 1; i++) {
            graph[minWay[i]][minWay[i + 1]] -= minFlow;
            graph[minWay[i + 1]][minWay[i]] += minFlow;
        }
        minWay = bfs(start, end, graph);
    }
    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;
    CGraph graph = CGraph(n);
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        graph.add(a, b, w);
    }
    cout << edmKarp(1, n, graph.getGraph()) << endl;
}

