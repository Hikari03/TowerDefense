#include "SniperTower.h"

#include <utility>

SniperTower::SniperTower(const Tower & tower) : Tower(tower){
    ch = "S";
    id = 4;
    damage = tower.getDamage() * config.towerSniperDamageScalar;
    range = tower.getRange() + config.towerSniperRangeScalar;
    cooldown = (tower.getCooldown() + config.towerSniperCooldownScalar) > 1 ? tower.getCooldown() + config.towerSniperCooldownScalar : 1;
    level = tower.getLevel();
    upgradeCost = tower.getUpgradeCost();
    sellPrice = tower.getSellPrice();
}

SniperTower::SniperTower(int level, double damage, int range, int cooldown, int pendingCooldown, int upgradeCost,
                         int sellPrice, shared_ptr<Targeting> towerTargeting, Coord &position, ConfigHolder &holder)
        : Tower(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, std::move(towerTargeting), position,
                holder) { ch = "S"; id = 4; }

void SniperTower::printChar() const {
    cout << "\033[1;32;45m" << ch << "\033[0m"; //purple background
}


