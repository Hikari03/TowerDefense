#ifndef TOWER_DEFENCE_MINION_H
#define TOWER_DEFENCE_MINION_H

#include "Enemy.h"

/**
 * @brief Basic enemy with no special abilities
 */
class Minion : public Enemy {
public:
    Minion(int lvl, Coord & position, ConfigHolder & config);
    Minion(int lvl, Coord & position, double healthI, ConfigHolder & config);
    Minion(const Minion & other);

    void printChar() const override;
};


#endif //TOWER_DEFENCE_MINION_H
