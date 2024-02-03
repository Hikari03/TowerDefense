#include <cmath>
#include "Coord.h"

Coord::Coord(int x, int y) : x(x), y(y) {}

bool Coord::operator==(const Coord & other) const {
    return x == other.x && y == other.y;
}

bool Coord::operator!=(const Coord & other) const {
    return !(*this == other);
}

double Coord::distance(const Coord & other) const {
    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
}