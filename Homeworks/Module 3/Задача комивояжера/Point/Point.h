#pragma once

struct Point {
    double x;
    double y;
};

double Dist(const Point &a, const Point &b);

double SqrDist(const Point &a, const Point &b);