#include "Dragon.h"

Dragon::Dragon(int lvl, Coord &position, ConfigHolder & config): Enemy(lvl, position, config){
    ch = "D";
    name = "Dragon";
    maxHealth = health = config.enemyDragonHealthScalar * lvl;
    reward = config.enemyDragonRewardScalar * lvl;
    invisibleCounter = config.enemyDragonInvisibilityDuration;
    speed = config.enemyDragonSpeed;
}

Dragon::Dragon(int lvl, Coord &position, double healthI, bool attackedBefore, int invisibleCounter, ConfigHolder & config): Enemy(lvl, position, config),
                invisible( (attackedBefore && invisibleCounter > 0) ), attackedBefore(attackedBefore), invisibleCounter(invisibleCounter){
    ch = "D";
    name = "Dragon";
    health = healthI;
    maxHealth = config.enemyDragonHealthScalar * lvl;
    if(health > maxHealth) health = maxHealth;
    reward = config.enemyDragonRewardScalar * lvl;
    speed = config.enemyDragonSpeed;
}

Dragon::Dragon(const Dragon & other) = default;

const Coord & Dragon::move() {
    Enemy::move();

    if(invisible)
    {
        --invisibleCounter;
        if(invisibleCounter == 0)
        {
            invisible = false;
        }
    }
    return position;
}

void Dragon::takeDamage(double damage) {
    if(!attackedBefore)
    {
        attackedBefore = true;
        invisible = true;
        Enemy::takeDamage(damage);
    }
    else if(!invisible)
    {
        Enemy::takeDamage(damage);
    }

}

void Dragon::printChar() const {
    if(invisible) {
        if (attacked)
            cout << "\033[1;41m"; //red background

        cout << "\033[38;5;51m" << ch << "\033[0m"; //blue character
    }
    else
        Enemy::printChar();
}

string Dragon::Export() const {
    string s;
    s+= "Enemy\n";
    s += name + '\n';
    s += to_string(level) + '\n';
    s += to_string(health) + '\n';
    s += to_string(position.x) + '\n';
    s += to_string(position.y) + '\n';
    s += to_string(attackedBefore) + '\n';
    s += to_string(invisibleCounter) + '\n';
    for (auto & spell : spells) {
        s += spell->Export();

    }

    s += "end\n";
    return s;
}