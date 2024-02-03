#include "Minion.h"

Minion::Minion(int lvl, Coord & position, ConfigHolder & config) : Enemy(lvl, position, config){
    ch = "M";
    name = "Minion";
    maxHealth = health = config.enemyMinionHealthScalar * lvl;
    reward = config.enemyMinionRewardScalar * lvl;
    speed = config.enemyMinionSpeed;
}

Minion::Minion(int lvl, Coord & position, double healthI, ConfigHolder & config) : Enemy(lvl, position, config){
    ch = "M";
    name = "Minion";
    health = healthI;
    maxHealth = config.enemyMinionHealthScalar * lvl;
    if(health > maxHealth) health = maxHealth;
    reward = config.enemyMinionRewardScalar * lvl;
    speed = config.enemyMinionSpeed;
}

Minion::Minion(const Minion & other) = default;

void Minion::printChar() const {
    Enemy::printChar();
}