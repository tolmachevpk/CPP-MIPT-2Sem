#pragma once
#include "../Point/Point.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class SortOutSolver {
public:
    // подсчёт длины пути
    double ReturnLength(const vector <Point> &points, const vector <int> &path);
    // перебор всех путей и поиск среди них кратчайшего
    double SortOut(const vector <Point> &points);
};