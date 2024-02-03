#include "Boss.h"

Boss::Boss(int lvl, Coord &position, ConfigHolder & config): Enemy(lvl, position, config){
    ch = "B";
    name = "Boss";
    maxHealth = health = config.enemyBossHealthScalar * lvl;
    reward = config.enemyBossRewardScalar * lvl;
    speed = config.enemyBossSpeed;
}

Boss::Boss(int lvl, Coord &position, double healthI, ConfigHolder & config): Enemy(lvl, position, config){
    ch = "B";
    name = "Boss";
    health = healthI;
    maxHealth = config.enemyBossHealthScalar * lvl;
    if(health > maxHealth) health = maxHealth;
    reward = config.enemyBossRewardScalar * lvl;
    speed = config.enemyBossSpeed;
}

Boss::Boss(const Boss & other) = default;

const Coord & Boss::move(){
    Enemy::move();
    if( !isDead() ){
        health += config.enemyBossRegenerationScalar * level;
        if( health > maxHealth)
            health = maxHealth;
    }
    return position;
}

void Boss::printChar() const {
    Enemy::printChar();
}