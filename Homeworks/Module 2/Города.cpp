/* Проблема заключалась в том, что я алгоритм Флойда и другие алгоритмы реализовывал
 * в самом классе, а не в отдельной функции. Сейчас я внес исправления.
 *
 *
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;
const int INF = 1000000000;

class IGraph {
public:
    IGraph(int n) : n(n) {
        w.resize(n);
        dist.resize(n, INF);
    }

    void addEdge(int start, int finish, int val) {
        w[start].push_back(make_pair(finish, val));
        w[finish].push_back(make_pair(start, val));
    }

    vector<vector<pair<int, int>>> getW() {
        return w;
    }

    int getN() {
        return n;
    }

private:
    int n;
    vector<vector<pair<int, int>>> w;
};


// вынесенная функция
int findMinDist(int start, int finish, int n, vector<vector<pair<int, int>>> w) {
    set<pair<int, int>> unused;
    vector<int> dist;
    dist.resize(n, INF);
    dist[start] = 0;
    unused.insert(make_pair(0, start));
    while (!unused.empty()) {
        int i = unused.begin()->second;
        unused.erase(unused.begin());
        for (auto edge : w[i]) {
            int j = edge.first;
            int wt = edge.second;
            if (dist[i] + wt < dist[j]) {
                unused.erase(make_pair(dist[j], j));
                dist[j] = dist[i] + wt;
                unused.insert(make_pair(dist[j], j));
            }
        }
    }
    return dist[finish];
}


int main() {
    int n, m;
    cin >> n >> m;
    IGraph graph(n);
    for (int i = 0; i < m; i++) {
        int a, b, result;
        cin >> a >> b >> result;
        graph.addEdge(a, b, result);
    }
    int start, finish;
    cin >> start >> finish;
    cout << findMinDist(start, finish, graph.getN(), graph.getW()) << endl;
}

