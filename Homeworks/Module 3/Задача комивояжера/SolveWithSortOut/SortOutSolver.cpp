#include "SortOutSolver.h"

double SortOutSolver::ReturnLength(const vector<Point> &points, const vector<int> &path) {
    double answer = Dist(points[path[0]], points[path[path.size()-1]]);
    for( int i = 0; i < path.size() - 1; i++ ) {
        answer += Dist(points[path[i]], points[path[i+1]]);
    }

    return answer;
}

double SortOutSolver::SortOut(const vector<Point> &points) {
    int n = points.size();
    vector <int> permutation;
    double minn = 1000000;

    for( int i = 0; i < n; i++ ) {
        permutation.push_back(i);
    }

    do {
        minn = min(minn, ReturnLength(points, permutation));
    } while( next_permutation(permutation.begin(), permutation.end()) );

    return minn;
}