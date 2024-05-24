typedef unsigned uint;
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>

struct Worker {
    std::string name;
    uint trustworthiness;
    uint labor_cost;
    uint work_speed;
    uint morale;

  public:
    Worker(std::string n, uint t, uint l = 100, uint w = 100, uint m = 100)
        : name(n), trustworthiness(t), labor_cost(l), work_speed(w),
          morale(m){};
    operator std::string() const {
        return std::string("") + std::to_string(trustworthiness) + "," +
               std::to_string(labor_cost) + "," + std::to_string(work_speed) +
               "," + std::to_string(morale);
    }
};

#include "technology.cpp"

class Contraption {
    uint maintenance = 0;
};

class Game {
    uint money;
    std::set<Worker> workers;
    std::set<Technology> technologies;
};

int main() {
    std::cout << (std::string)Worker("me", 1, 2, 3, 4) << std::endl
              << Technology().cost << std::endl;
    return 0;
}
