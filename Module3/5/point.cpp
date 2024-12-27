#include "point.h"
#include <iostream>
std::vector<Point> Point::generatePoints(int n) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0, 1);

    for (int i = 0; i < n; ++i) {
        double u1 = dist(gen);
        double u2 = dist(gen);

        double r = std::sqrt(-2.0 * std::log(u1));
        double theta = 2.0 * M_PI * u2;

        double x = r * std::cos(theta);
        double y = r * std::sin(theta);

        points.push_back({x, y});
    }
    return points;
}


double Point::distance(const Point& a, const Point& b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}