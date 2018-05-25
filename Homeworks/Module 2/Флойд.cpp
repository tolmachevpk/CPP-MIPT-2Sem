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
        w.resize(n, vector<double>(n, INF));
    }

    void cinGraph() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int a;
                cin >> a;
                w[i][j] = a;
            }
        }
    }

    int getN() {
        return n;
    }

    vector<vector<double>> getW() {
        return w;
    }

private:
    int n;
    vector<vector<double>> w;
};


// вынесенная функция
void findMinDist(const vector<vector<double>> &w, const int &n) {
    int A[n + 1][n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[0][i][j] = w[i][j];
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[k][i][j] = min(A[k - 1][i][j], A[k - 1][i][k - 1] + A[k - 1][k - 1][j]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cout << A[n][i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int n;
    cin >> n;
    IGraph graph(n);
    graph.cinGraph();
    findMinDist(graph.getW(), graph.getN());
}

