#ifndef TOWER_DEFENCE_BOSS_H
#define TOWER_DEFENCE_BOSS_H


#include "Enemy.h"

/**
 * @brief Enemy with the most health and can heal
 */
class Boss : public Enemy {
public:
    Boss(int lvl, Coord & position, ConfigHolder & config);
    Boss(int lvl, Coord & position, double healthI, ConfigHolder & config);
    Boss(const Boss & other);

    /**
     * @brief Overrides move() for boss to implement healing
     * @details
     *      Moves enemy to next position in path and applies spells
     *
     * @return Position of enemy
     */
    const Coord & move() override;

    void printChar() const override;
};


#endif //TOWER_DEFENCE_BOSS_H
