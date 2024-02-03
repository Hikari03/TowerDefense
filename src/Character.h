#ifndef TOWER_DEFENCE_CHARACTER_H
#define TOWER_DEFENCE_CHARACTER_H


#include "Tile.h"
#include <iostream>

/**
 * @brief Used to print characters
 */
class Character : public Tile {
public:
    explicit Character(char c);
    Character(const Character & other) = default;
    explicit Character(const string & c);

    void printChar() const override;
};


#endif //TOWER_DEFENCE_CHARACTER_H
