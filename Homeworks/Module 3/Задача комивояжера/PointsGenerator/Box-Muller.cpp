#include "Box-Muller.h"

vector <Point> RandomPoints(int n) {
    vector <Point> points;

    for( int i = 0; i < n; i++ ) {
        double u = rand() % 2001 / 1000.0 - 1.0;
        double v = sqrt(1 - u * u) * (rand() % 2001 / 1000.0 - 1.0);
        double s = u * u + v * v;
        double p = sqrt(-2 * log(s) / s);

        if( fabs(s - 1) < 0.00001 ) {
            p = 0;
        }

        double x = 100 * u * p;
        int x_mod_100 = (int)x / 100;
        x -= x_mod_100 * 100;

        double y = 100 * v * p;
        int y_mod_100 = (int)y / 100;
        y -= y_mod_100 * 100;

        Point point;
        point.x = x;
        point.y = y;
        points.push_back(point);
    }

    return points;
};