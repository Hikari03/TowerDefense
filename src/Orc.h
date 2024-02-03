#ifndef TOWER_DEFENCE_ORC_H
#define TOWER_DEFENCE_ORC_H

#include "Enemy.h"


/**
 * @brief Tougher enemy with armor
 */
class Orc : public Enemy {
public:
    Orc(int lvl, Coord & position, ConfigHolder & config);
    Orc(int lvl, Coord & position, double healthI, ConfigHolder & config);
    Orc(const Orc & other);

    void takeDamage(double damage) override;

    void printChar() const override;
};

#endif //TOWER_DEFENCE_ORC_H
