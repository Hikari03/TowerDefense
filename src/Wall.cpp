#include "Wall.h"

Wall::Wall(const string & c) {
    ch = c;
    tileType = Type::WALL;
}

void Wall::printChar() const {
    cout << "\033[1;32m" << ch << "\033[0m";
}

Wall::Wall(const Wall & other) = default;