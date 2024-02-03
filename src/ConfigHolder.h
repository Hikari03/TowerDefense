#ifndef TOWER_DEFENCE_CONFIGHOLDER_H
#define TOWER_DEFENCE_CONFIGHOLDER_H

#include <string>

using namespace std;

/**
 * @brief Holds config values
 */
class ConfigHolder {

public:
    ~ConfigHolder() = default;

    string mapName;

    // Tower
    int towerCost;
    double towerDamage;
    int towerRange;
    int towerCooldown;
    int towerUpgradeCost;
    int towerSellPrice;

    int towerUpgradeCostScalar;
    double towerUpgradeSellPriceScalar;
    double towerUpgradeDamageScalar;

    int towerMaxLevel;

    // FireTower
    int towerFireIntensity;
    int towerFireIntensityScalar;

    // Tower specialize scalars
    double towerFireDamageScalar;
    int towerFireRangeScalar;
    int towerFireCooldownScalar;
    double towerIceDamageScalar;
    int towerIceRangeScalar;
    int towerIceCooldownScalar;
    double towerSniperDamageScalar;
    int towerSniperRangeScalar;
    int towerSniperCooldownScalar;
    

    // Enemy
    double enemyMinionHealthScalar;
    int enemyMinionSpeed;
    int enemyMinionRewardScalar;

    double enemyOrcHealthScalar;
    int enemyOrcSpeed;
    int enemyOrcRewardScalar;
    double enemyOrcArmor;

    double enemyDragonHealthScalar;
    int enemyDragonSpeed;
    int enemyDragonRewardScalar;
    int enemyDragonInvisibilityDuration;

    double enemyBossHealthScalar;
    int enemyBossSpeed;
    int enemyBossRewardScalar;
    int enemyBossRegenerationScalar;



};


#endif //TOWER_DEFENCE_CONFIGHOLDER_H
