#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

struct Point {
    double x;
    double y;
};

std::shared_ptr<std::vector<Point>> readFile(const std::string& filePath) {
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
    auto points = readFile("/home/lukasz/CLionProjects/pwr_racing/data");
    std::cout << points->size() << std::endl;

    for (auto p : *points) {
        std::cout << p.x << " " << p.y << std::endl;
    }

    return 0;
}
