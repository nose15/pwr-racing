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

// Funkcja określająca, czy wektor 0->A ma większy kąt względem osi X niż wektor 0->B
bool compare(Point& a, Point& b) {
    // Różnica iloczynów wektorowych między wektorem 0->A, a 0->B
    double crossDiff = (a.x - point0.x) * (b.y - point0.y) - (a.y - point0.y) * (b.x - point0.x);

    // Różnica iloczynów wektorowych równa 0 oznacza, że te wektory mają ten sam kąt względem osi X.
    // W tym przypadku wybieramy ten punkt, który jest bliżej.
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

template <typename T>
std::shared_ptr<std::vector<T>> stackToVec(std::stack<T> stack) {
    auto hullVec = std::make_shared<std::vector<Point>>();
    while (!stack.empty()) {
        hullVec->push_back(stack.top());
        stack.pop();
    }

    return hullVec;
}

// Algorytm umożliwiający znalezienie otoczki wypukłej, czyli takiej, która pomiędzy swoimi wierzchołkami nie
// ma kątów wklęsłych. Graham Scan polega na znalezieniu punktu najbliższego do osi X jako punkt 0, a następnie
// posortowaniu pozostałych punktów według kąta pomiędzy wektorem, który tworzą razem z punktem 0, a osią X.
// Iterując po tych punktach następnie "zawijamy się" wokół grupy punktów, a jeśli znajdziemy punkt, który
// otacza punkty w otoczce, to "odwijamy" tak długo, aż je otoczymy
std::shared_ptr<std::vector<Point>> grahamScan(std::shared_ptr<std::vector<Point>> points) {
    // znajdujemy punkt najbliższy do osi x
    double lowestY = points->at(0).y;

    for (int i = 1; i < points->size(); i++) {
        if (points->at(i).y < lowestY) {
            std::swap(points->at(0), points->at(i));
        }
    }

    point0 = points->at(0);

    // pozostałe punkty sortujemy rosnąco według kąta między osią X a wektorem o początku w punkcie 0,
    // a końcu w sprawdzanym punkcie
    std::sort(points->begin() + 1, points->end(), compare);
    std::stack<Point> hull;

    // dwa pierwsze punkty na pewno będą częścią otoczki, ponieważ wektor między nimi ma najmniejszy kąt względem
    // osi X oraz punkt 0 jest najbliżej osi x. To znaczy, że nie znajdziemy już punktu, który by je otoczył,
    // jedynie możliwe jest znalezienie punktu, który jest z nimi współliniowy
    hull.push(points->at(0));
    hull.push(points->at(1));

    // Mamy 2 pierwsze punkty otoczki. Teraz, aby znaleźć następne, iterujemy po wszystkich punktach
    // posortowanych rosnąco według kąta. Najpierw sprawdzamy, czy dodając dany punkt do otoczki uda się otoczyć punkty,
    // które już do niej należą. Aby to sprawdzić należy określić w jakiej orientacji względem siebie są 2 ostatnie
    // punkty oraz obecnie sprawdzany punkt. Jeśli są one ustawione w kierunku przeciwnym do wskazówek zegara, to znaczy,
    // że prosta utworzona między przedostatnim punktem otoczki a obecnie sprawdzanym punktem otoczy ostatni punkt otoczki.
    // Z tego powodu usuwamy ostatni punkt z otoczki.
    for (int i = 2; i < points->size(); i++) {
        Point p = points->at(i);

        // Tak długo jak będziemy znajdować kolejne trójki, które są ustawione w kierunku przeciwnym do wskazówek zegara,
        // możemy je usuwać z otoczki na podstawie zależności opisanej wyżej.
        while (hull.size() > 1 && isClockwise(nextToTop(hull), hull.top(), p)) {
            hull.pop();
        }

        hull.push(p);
    }

    return stackToVec(hull);
}

std::shared_ptr<std::vector<Point>> readPointsFromFile(const std::string& filePath) {
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
    auto points = readPointsFromFile("/home/lukasz/CLionProjects/pwr_racing/data");
    auto hull = grahamScan(points);

    for (auto p : *hull) {
        std::cout << p.x << " " << p.y << std::endl;
    }

    return 0;
}
