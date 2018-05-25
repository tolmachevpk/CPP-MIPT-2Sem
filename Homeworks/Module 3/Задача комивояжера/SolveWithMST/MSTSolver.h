#pragma once
#include "../Point/Point.h"
#include <iostream>
#include <vector>

using namespace std;

class MSTSolver {
public:
    // поиск минимального остова
    void PrimAlgorithm(const vector <Point> &points);
    // поиск эйлерова цикла на минимальном остове
    void DfsForMST(int v, vector <bool> &visited);
    double FindEulerCycle(const vector <Point> &points);
private:
    // граф минимального остова
    vector <vector <int> > mst;
    // эйлеров цикл минимального остова
    vector <int> eulerCycle;
};