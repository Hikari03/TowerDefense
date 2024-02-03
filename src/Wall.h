
#ifndef TOWER_DEFENCE_WALL_H
#define TOWER_DEFENCE_WALL_H

#include "Tile.h"
#include <iostream>

/**
 * @brief Wall tile
 */
class Wall : public Tile {
public:
    explicit Wall(const string & c);
    Wall(const Wall & other);

    void printChar() const override;

};


#endif //TOWER_DEFENCE_WALL_H
