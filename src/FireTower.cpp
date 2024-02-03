#include "FireTower.h"

#include <utility>

FireTower::FireTower(const Tower & tower) : Tower(tower){
    ch = "F";
    id = 2;
    damage = tower.getDamage() * config.towerFireDamageScalar;
    range = tower.getRange() + config.towerFireRangeScalar;
    cooldown = (tower.getCooldown() + config.towerFireCooldownScalar) > 1 ? tower.getCooldown() + config.towerFireCooldownScalar : 1;
    level = tower.getLevel();
    upgradeCost = tower.getUpgradeCost();
    sellPrice = tower.getSellPrice();
    intensity = config.towerFireIntensity;
}

FireTower::FireTower(int level, double damage, int range, int cooldown, int pendingCooldown,
          int upgradeCost, int sellPrice, shared_ptr<Targeting> towerTargeting, Coord & position, int intensity, ConfigHolder & config)
          : Tower(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, std::move(towerTargeting), position, config), intensity(intensity)
          {ch = "F"; id = 2;}

shared_ptr<Enemy> FireTower::attack(vector<shared_ptr<Enemy>> & enemies) {
    auto tmp = Tower::attack(enemies);
    if(tmp != nullptr)
        tmp->getSpell(make_shared<FireSpell>(damage, 3+level, intensity));
    return tmp;
}

void FireTower::upgrade() {
    Tower::upgrade();
    intensity += config.towerFireIntensityScalar;
}

void FireTower::printChar() const {
    cout << "\033[1;32;41m" << ch << "\033[0m"; //red background
}

string FireTower::Export() const {
    string s;
    s += "FireTower\n";
    s += to_string(id) + '\n';
    s += to_string(level) + '\n';
    s += to_string(damage) + '\n';
    s += to_string(range) + '\n';
    s += to_string(cooldown) + '\n';
    s += to_string(pendingCooldown) + '\n';
    s += to_string(upgradeCost) + '\n';
    s += to_string(sellPrice) + '\n';
    s += towerTargeting->targeting() + '\n';
    s += to_string(position.x) + '\n';
    s += to_string(position.y) + '\n';
    s += to_string(intensity) + '\n';
    s += "end\n";

    return s;
}