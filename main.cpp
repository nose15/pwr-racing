#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <cmath>
#include <algorithm>
#include <stack>

struct Point {
    double x;
    double y;
};

Point point0;

bool compare(Point& a, Point& b) {
    double crossDiff = (a.x - point0.x) * (b.y - point0.y) - (a.y - point0.y) * (b.x - point0.x);

    if (crossDiff == 0) {
        double distDiff = std::pow(a.x - point0.x, 2) + std::pow(a.y - point0.y, 2) - std::pow(b.x - point0.x, 2) - std::pow(b.y - point0.y, 2);
        return distDiff < 0;
    }

    return crossDiff > 0;
}

bool isClockwise(Point& a, Point& b, Point& c) {
    double val = ((b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y));
    return val > 0;
}

template <typename T>
T& nextToTop(std::stack<T> stack) {
    T top = stack.top();
    stack.pop();
    T& ntt = stack.top();

    stack.push(top);
    return ntt;
}

std::shared_ptr<std::vector<Point>> grahamScan(std::shared_ptr<std::vector<Point>> points) {
    double lowestY = points->at(0).y;

    // find point with lowest y and set points[0] as that point
    for (int i = 1; i < points->size(); i++) {
        if (points->at(i).y < lowestY) {
            std::swap(points->at(0), points->at(i));
        }
    }

    point0 = points->at(0);

    // sort remaining points by polar angle between them and points[0]
    std::sort(points->begin() + 1, points->end(), compare);
    std::stack<Point> hull;

    hull.push(points->at(0));
    hull.push(points->at(1));

    for (int i = 2; i < points->size(); i++) {
        Point p = points->at(i);

        while (hull.size() > 1 && isClockwise(nextToTop(hull), hull.top(), p)) {
            hull.pop();
        }

        hull.push(p);
    }

    auto hullVec = std::make_shared<std::vector<Point>>();
    while (!hull.empty()) {
        hullVec->push_back(hull.top());
        hull.pop();
    }

    return hullVec;
}

std::shared_ptr<std::vector<Point>> readPoints(const std::string& filePath) {
    std::ifstream file;
    file.open(filePath);

    size_t vecSize;
    std::string line;

    if (getline(file, line)) {
        vecSize = std::stoi(line);
    } else {
        throw std::length_error("No lines in a file");
    }

    auto res = std::make_shared<std::vector<Point>>(vecSize);

    uint8_t idx = 0;
    while (getline(file, line)) {
        uint32_t spacePos = line.find(' ');
        Point point{
                std::stod(line.substr(0,spacePos)),
                std::stod(line.substr(spacePos, line.size() - 1))
        };
        res->at(idx) = point;
        idx++;
    }

    return res;
}

int main() {
    auto points = readPoints("/home/lukasz/CLionProjects/pwr_racing/data");
    auto hull = grahamScan(points);

    for (auto p : *hull) {
        std::cout << p.x << " " << p.y << std::endl;
    }

    return 0;
}
