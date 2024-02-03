
#ifndef TOWER_DEFENCE_ICETOWER_H
#define TOWER_DEFENCE_ICETOWER_H


#include "Tower.h"
#include "IceSpell.h"

/**
 * @brief Tower that casts IceSpell
 */
class IceTower : public Tower {
public:
    explicit IceTower(const Tower & tower);

    IceTower(int level, double damage, int range, int cooldown, int pendingCooldown,
             int upgradeCost, int sellPrice, shared_ptr<Targeting> towerTargeting, Coord & position, ConfigHolder & holder);

    IceTower(const IceTower & other) = default;

    shared_ptr<Enemy> attack(vector<shared_ptr<Enemy>> & enemies) override;

    void printChar() const override;
};

#endif //TOWER_DEFENCE_ICETOWER_H
