//
// Created by lukasz on 17.03.25.
//

#ifndef PWR_RACING_CONVEX_HULL_CALCULATOR_HPP
#define PWR_RACING_CONVEX_HULL_CALCULATOR_HPP

#include <cmath>
#include <point.hpp>
#include <memory>
#include <vector>

bool compare(Point& a, Point& b);
bool isClockwise(Point& a, Point& b, Point& c);
std::shared_ptr<std::vector<Point>> grahamScan(std::shared_ptr<std::vector<Point>> points);

#endif //PWR_RACING_CONVEX_HULL_CALCULATOR_HPP
