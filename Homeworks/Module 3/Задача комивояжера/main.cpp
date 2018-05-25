#include "Point/Point.h"
#include "SolveWithMST/MSTSolver.h"
#include "SolveWithSortOut/SortOutSolver.h"
#include "PointsGenerator/Box-Muller.h"
using namespace std;

int main() {
    int n, m;
    cout << "Введите количество точек:" << endl;
    cin >> n;
    cout << "Введите количество тестов" << endl;
    cin >> m;

    double average = 0;
    for( int i = 0; i < m; i++ ) {
        vector<Point> points = RandomPoints(n);

        MSTSolver solver1;
        solver1.PrimAlgorithm(points);
        SortOutSolver solver2;

        double answer1 = solver1.FindEulerCycle(points);
        double answer2 = solver2.SortOut(points);

        double deviation = answer1 / answer2;
        average += deviation;

        cout << i << ") " << answer1 << " / " << answer2 << " = " << deviation << endl;
    }

    average /= m;
    cout << "Среднее отклонение: " << average << endl;
}