#include "IceTower.h"

IceTower::IceTower(const Tower & tower) : Tower(tower){
    ch = "I";
    id = 3;
    damage = tower.getDamage() * config.towerIceDamageScalar;
    range = tower.getRange() + config.towerIceRangeScalar;
    cooldown = (tower.getCooldown() + config.towerIceCooldownScalar) > 1 ? tower.getCooldown() + config.towerIceCooldownScalar : 1;
    level = tower.getLevel();
    upgradeCost = tower.getUpgradeCost();
    sellPrice = tower.getSellPrice();
}

IceTower::IceTower(int level, double damage, int range, int cooldown, int pendingCooldown, int upgradeCost,
                   int sellPrice, shared_ptr<Targeting> towerTargeting, Coord &position, ConfigHolder &holder) :
                   Tower(level, damage, range, cooldown, pendingCooldown, upgradeCost,
                                                  sellPrice, std::move(towerTargeting), position, holder) { ch = "I"; id = 3; }

shared_ptr<Enemy> IceTower::attack (vector<shared_ptr<Enemy>> & enemies){
    auto tmp = Tower::attack(enemies);
    if(tmp != nullptr)
        tmp->getSpell(make_shared<IceSpell>(3+level));
    return tmp;
}

void IceTower::printChar() const {
    cout << "\033[1;32;44m" << ch << "\033[0m"; //blue background
}

