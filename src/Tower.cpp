#include <iostream>
#include <utility>
#include "Tower.h"

Tower::Tower(shared_ptr<Targeting> towerTargeting, Coord & position, ConfigHolder & config): towerTargeting(std::move(towerTargeting)), position(position), config(config) {
    ch = "T";
    id = 1;
    damage = config.towerDamage;
    range = config.towerRange;
    cooldown = config.towerCooldown;
    level = 1;
    upgradeCost = config.towerUpgradeCost;
    sellPrice = config.towerSellPrice;
    tileType = Tile::Type::TOWER;
}

Tower::Tower(int level, double damage, int range, int cooldown, int pendingCooldown,
          int upgradeCost, int sellPrice,  shared_ptr<Targeting> towerTargeting, Coord & position, ConfigHolder & config)
          : id(1), level(level), damage(damage), range(range), cooldown(cooldown), pendingCooldown(pendingCooldown),
          upgradeCost(upgradeCost), sellPrice(sellPrice), towerTargeting(std::move(towerTargeting)), position(position), config(config)
          {ch = "T";
          tileType = Tile::Type::TOWER;
          }

// ##### Tower Methods #################################################################################################

void Tower::upgrade() {
    level++;
    damage *= config.towerUpgradeDamageScalar;
    upgradeCost += config.towerUpgradeCostScalar;
    sellPrice = static_cast<int>(upgradeCost * static_cast<double>(config.towerUpgradeSellPriceScalar));
}

int Tower::sell() {
    return sellPrice;
}

double Tower::getDamage() const {
    return damage;
}

int Tower::getRange() const {
    return range;
}

int Tower::getCooldown() const {
    return cooldown;
}

int Tower::getLevel() const {
    return level;
}

int Tower::getUpgradeCost() const {
    return upgradeCost;
}

int Tower::getSellPrice() const {
    return sellPrice;
}

const Coord & Tower::getPosition() const {
    return position;
}

int Tower::getID() const {
    return id;
}


shared_ptr<Enemy> Tower::attack(vector<shared_ptr<Enemy>> & enemies) {

    shared_ptr<Enemy> tmp = towerTargeting->getTarget(enemies, position, range);

    if(tmp == nullptr)
        return tmp;

    if(pendingCooldown != 0){
        --pendingCooldown;
        return nullptr;
    }

    tmp->takeDamage(damage);
    pendingCooldown = cooldown;
    return tmp;
}

void Tower::setTargeting(shared_ptr<Targeting> targeting) {
    towerTargeting = std::move(targeting);
}

const string & Tower::getTargeting() const {
    return towerTargeting->targeting();
}

void Tower::printChar() const {
    cout << "\033[1;32m" << ch << "\033[0m"; //green character
}

string Tower::Export() const {
    string s;
    s += "Tower\n";
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
    s += "end\n";

    return s;
}
