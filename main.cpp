#include <iostream>
#include <utils.hpp>
#include <convex_hull.hpp>

int main() {
    auto points = readPointsFromFile("../data");
    auto hull = grahamScan(points);

    for (auto p : *hull) {
        std::cout << p.x << " " << p.y << std::endl;
    }

    return 0;
}
