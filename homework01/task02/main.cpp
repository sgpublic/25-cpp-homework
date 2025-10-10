#include <cmath>
#include <iostream>
#include <vector>

class Point {
private:
    const int x;
    const int y;

public:
    Point() = delete;

    Point(int x, int y): x(x), y(y) {
    }

    void Display() {
        std::cout << "(" << this->x << "," << this->y << ")" << std::endl;
    }

    double Lenth(const Point *other) {
        return std::sqrt(std::pow(x - other->x, 2) + std::pow(y - other->y, 2));
    }
};

int main() {
    std::vector<Point> points;
    double totalLength = 0;

    for (int i = 0; i < 10; i++) {
        std::cout << "Input x,y:";
        int x, y;
        std::cin >> x >> y;
        Point point(x, y);
        points.push_back(point);
    }

    for (auto point : points) {
        point.Display();
    }

    for (int i = 1; i < points.size(); i++) {
        Point point1 = points.at(i-1);
        Point point2 = points.at(i);
        totalLength += point1.Lenth(&point2);
    }

    std::cout << "Length:" << totalLength;

    return 0;
}