#include "MSTSolver.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void MSTSolver::PrimAlgorithm(const vector <Point> &points) {
    const int INF = 1000000;
    int n = points.size();
    mst.assign(n, vector <int>());

    // min_e[i] - минимальный вес допустимого ребра из i в уже посещенную вершину
    vector <double> min_e(n, INF);
    min_e[0] = 0;

    // forVisit - сет еще не посещенных вершин
    set <pair <double, int>> forVisit;
    forVisit.insert({0, 0});

    // parents[i] - ребро из остовного дерева, до которого минимально расстояние из i
    vector <int> parents(n, -1);

    // visited - сет вершин, уже взятых в мин. остов
    set <int> visited;

    for( int i = 0; i < n; i++ ) {
        if( forVisit.empty() ) {
            cout << "YES";
            break;
        }

        // берем номер непосещенной вершины, из которой выходит минимальное ребро в посещенную
        int v = forVisit.begin()->second;
        forVisit.erase(forVisit.begin());
        visited.insert(v);

        // если это не первая добавленная вершина, то добавляем ребро в mst
        if( v != 0 ) {
            mst[v].push_back(parents[v]);
            mst[parents[v]].push_back(v);
        }

        // релаксируем метки для ее соседей
        for(int j = 0; j < points.size(); j++ ) {
            if( v == j ) continue;
            int to = j;
            double weight = SqrDist(points[v], points[j]);
            if( weight < min_e[to] && visited.count(to) == 0 ) {
                forVisit.erase({min_e[to], to});
                min_e[to] = weight;
                forVisit.insert({min_e[to], to});
                parents[to] = v;
            }
        }
    }

}

void MSTSolver::DfsForMST(int v, vector <bool> &visited) {
    visited[v] = true;
    eulerCycle.push_back(v);

    for( int i = 0; i < mst[v].size(); i++ ) {
        if( !visited[mst[v][i]] ) {
            DfsForMST(mst[v][i], visited);
        }
    }
}

double MSTSolver::FindEulerCycle(const vector <Point> &points) {
    int n = mst.size();
    vector <bool> visited(n, false);

    DfsForMST(0, visited);

    eulerCycle.push_back(0);
    double answer = 0;
    for( int i = 0; i < eulerCycle.size() - 1; i++ ) {
        answer += Dist(points[eulerCycle[i]], points[eulerCycle[i + 1]]);
    }

    return answer;
}