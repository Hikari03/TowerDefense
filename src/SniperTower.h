#ifndef TOWER_DEFENCE_SNIPERTOWER_H
#define TOWER_DEFENCE_SNIPERTOWER_H

#include "Tower.h"

/**
 * @brief Tower that deals high damage with long range and slow fire rate
 */
class SniperTower : public Tower {
public:
    explicit SniperTower(const Tower & tower);

    SniperTower(int level, double damage, int range, int cooldown, int pendingCooldown,
                int upgradeCost, int sellPrice, shared_ptr<Targeting> towerTargeting, Coord & position, ConfigHolder & holder);

    SniperTower(const SniperTower & other) = default;

    void printChar() const override;
};


#endif //TOWER_DEFENCE_SNIPERTOWER_H
