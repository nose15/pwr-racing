//
// Created by lukasz on 17.03.25.
//

#ifndef PWR_RACING_POINT_HPP
#define PWR_RACING_POINT_HPP

#include <memory>
#include <vector>
#include <fstream>

struct Point {
    double x;
    double y;
};

std::shared_ptr<std::vector<Point>> readPointsFromFile(const std::string& filePath);

#endif //PWR_RACING_POINT_HPP
