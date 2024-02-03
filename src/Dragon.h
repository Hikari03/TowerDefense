#ifndef TOWER_DEFENCE_DRAGON_H
#define TOWER_DEFENCE_DRAGON_H

#include "Enemy.h"

/**
 * @brief Enemy that can turn invisible after being attacked
 */
class Dragon : public Enemy {
public:
    Dragon(int lvl, Coord & position, ConfigHolder & config);
    Dragon(int lvl, Coord & position, double healthI, bool attackedBefore, int invisibleCounter, ConfigHolder & config);
    Dragon(const Dragon & other);

    const Coord & move() override;

    void takeDamage(double damage) override;

    string Export() const override;

    void printChar() const override;

private:
    bool invisible = false;
    bool attackedBefore = false;
    int invisibleCounter;
};


#endif //TOWER_DEFENCE_DRAGON_H
