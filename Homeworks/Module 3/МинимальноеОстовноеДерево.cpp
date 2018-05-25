#include <iostream>
#include <vector>
#include <set>

using namespace std;

class CGraph {
public:
    CGraph(int n) {
        g.resize(n + 1);
    }

    void add(int a, int b, int w) {
        g[a].push_back(make_pair(b, w));
        g[b].push_back(make_pair(a, w));
    }

    vector<vector<pair<int, int>>> getGraph() {
        return g;
    }

private:
    vector<vector<pair<int, int>>> g;
};

int prima(vector<vector<pair<int, int>>> g, int n) {
vector<bool> used(n + 1, false);
const int INF = 1000000000;
vector<int> min_e (n + 1, INF), sel_e (n + 1, -1);
min_e[1] = 0;
set<pair<int,int>> q;
q.insert (make_pair (0, 1));
int s = 0;
for(int i=0; i <= n; ++i) {
if (q.empty()) {
break;
}
int v = q.begin()->second;
used[v] = true;
s += q.begin()->first;
q.erase (q.begin());
for (size_t j = 0; j < g[v].size(); ++j) {
int to = g[v][j].first,
        cost = g[v][j].second;
if(used[to]) {
continue;
}
if (cost < min_e[to]) {
q.erase (make_pair (min_e[to], to));
min_e[to] = cost;
sel_e[to] = v;
q.insert (make_pair (min_e[to], to));
}
}
}
return s;
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;
    CGraph graph(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.add(a, b, c);
    }
    cout << prima(graph.getGraph(), n) << endl;
}

