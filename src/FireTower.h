#ifndef TOWER_DEFENCE_FIRETOWER_H
#define TOWER_DEFENCE_FIRETOWER_H

#include "Tower.h"
#include "FireSpell.h"

/**
 * @brief Tower that casts FireSpell
 */
class FireTower : public Tower {
public:
    explicit FireTower(const Tower & tower);

    FireTower(int level, double damage, int range, int cooldown, int pendingCooldown,
              int upgradeCost, int sellPrice, shared_ptr<Targeting> towerTargeting, Coord & position, int intensity, ConfigHolder & holder);

    FireTower(const FireTower & other) = default;


    void printChar() const override;

    void upgrade() override;

    shared_ptr<Enemy> attack(vector<shared_ptr<Enemy>> & enemies) override;

    /*
     * returns string for exporting with intensity
     */
    string Export() const override;

private:
    int intensity;
};


#endif //TOWER_DEFENCE_FIRETOWER_H
