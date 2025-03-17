//
// Created by lukasz on 17.03.25.
//

#ifndef PWR_RACING_UTILS_HPP
#define PWR_RACING_UTILS_HPP

#include <stack>
#include <memory>
#include <vector>
#include <fstream>
#include <point.hpp>

template <typename T>
T& nextToTop(std::stack<T> stack) {
    T top = stack.top();
    stack.pop();
    T& ntt = stack.top();

    stack.push(top);
    return ntt;
}

template <typename T>
std::shared_ptr<std::vector<T>> stackToVec(std::stack<T> stack) {
    auto hullVec = std::make_shared<std::vector<Point>>();
    while (!stack.empty()) {
        hullVec->push_back(stack.top());
        stack.pop();
    }

    return hullVec;
}

std::shared_ptr<std::vector<Point>> readPointsFromFile(const std::string& filePath);

#endif //PWR_RACING_UTILS_HPP
