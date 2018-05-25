/* Проблема заключалась в том, что я алгоритм Флойда и другие алгоритмы реализовывал
 * в самом классе, а не в отдельной функции. Сейчас я внес исправления.
 *
 * Задача решена модификацией алгоритма Флойда.
 */


#include <iostream>
#include <vector>
#include <set>


using namespace std;


class IGraph {
public:
    IGraph(int n) : n(n) {
        w.resize(n, vector<double>(n, INF));
    }

    void cinGraph() {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) {
                    w[i][j] = 1;
                    continue;
                }
                double a;
                cin >> a;
                if(a == -1) {
                    a = INF;
                }
                w[i][j] = a;
            }
        }
    }

    vector<vector<double>> getW() {
        return w;
    }

    int getN() {
        return n;
    }

private:
    const int INF = 1000000000;
    int n;
    vector<vector<double>> w;
};


// вынесенная функция
string findMinDist(const int &n, const  vector<vector<double>> &w) {
    int A[n + 1][n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            A[0][i][j] = w[i][j];
        }
    }
    for (int k = 1; k <= n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                A[k][i][j] = max(A[k - 1][i][j], A[k - 1][i][k - 1] * A[k - 1][k - 1][j]);
            }
        }
    }
    for(int i = 0; i < n; i++) {
        if(A[n][i][i] > 1)
            return "YES";
    }
    return "NO";
}


int main() {
    int n;
    cin >> n;
    IGraph graph(n);
    graph.cinGraph();
    cout << findMinDist(graph.getN(), graph.getW()) << endl;
}