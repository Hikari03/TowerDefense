#include "Orc.h"

Orc::Orc(int lvl, Coord &position, ConfigHolder & config): Enemy(lvl, position, config){
    ch = "O";
    name = "Orc";
    maxHealth = health = config.enemyDragonHealthScalar * lvl;
    reward = config.enemyOrcRewardScalar * lvl;
    speed = config.enemyOrcSpeed;
}

Orc::Orc(int lvl, Coord &position, double healthI, ConfigHolder & config): Enemy(lvl, position, config){
    ch = "O";
    name = "Orc";
    health = healthI;
    maxHealth = config.enemyDragonHealthScalar * lvl;
    if(health > maxHealth) health = maxHealth;
    reward = config.enemyOrcRewardScalar * lvl;
    speed = config.enemyOrcSpeed;
}

Orc::Orc(const Orc & other) = default;

void Orc::takeDamage(double damage) {
    Enemy::takeDamage(damage-damage*config.enemyOrcArmor);
}

void Orc::printChar() const {
    Enemy::printChar();
}