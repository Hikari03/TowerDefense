#ifndef TOWER_DEFENCE_COORD_H
#define TOWER_DEFENCE_COORD_H
#include <iostream>
using namespace std;

/**
 * @brief Used to store coordinates
 */
class Coord {
public:

    Coord() = default;
    ~Coord() = default;
    Coord(int x, int y);
    Coord(const Coord & other) = default;

    bool operator==(const Coord & other) const;

    bool operator!=(const Coord & other) const;

    friend ostream & operator << (ostream & os, const Coord & coord){
        os << "(" << coord.x << ", " << coord.y << ")";
        return os;
    }

    /**
     * @brief Calculates distance between two coordinates
     *
     * @details
     *      Calculates distance between two coordinates using Pythagorean theorem
     *
     * @param other - other coordinate
     * @return double - distance between two coordinates
     */
    double distance(const Coord & other) const;

    int x;
    int y;


};


#endif //TOWER_DEFENCE_COORD_H
