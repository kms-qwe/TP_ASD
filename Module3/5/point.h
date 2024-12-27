#ifndef POINT_H
#define POINT_H

#include <vector>
#include <cmath>
#include <random>
#include <iostream> 

struct Point {
    double x, y;

    static std::vector<Point> generatePoints(int n);
    static double distance(const Point& a, const Point& b);
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
};

#endif
