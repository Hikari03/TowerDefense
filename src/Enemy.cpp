#include <iostream>
#include "Enemy.h"

Enemy::Enemy(int lvl, Coord & position, ConfigHolder & config) : level(lvl), position(position), config(config){
    speed = 0;
    tileType = Tile::Type::ENEMY;
}

Enemy::Enemy(const Enemy & other) : name(other.name), attacked(other.attacked), maxHealth(other.maxHealth), health(other.health),
                                    reward(other.reward), level(other.level), position(other.position), path(other.path),
                                    pathIndex(other.pathIndex), spells(other.spells), config(other.config) {
ch = other.ch;
speed = other.speed;
tileType = other.tileType;
}

// ##### Enemy Methods #################################################################################################

void Enemy::importPath(const vector<Coord> & pathT) {
    path = pathT;
}

void Enemy::syncPosition() {
    for( unsigned long i = 0; i < path.size(); i++ ) {
        if( path[i] == position ) {
            pathIndex = static_cast<int>(i);
        }
    }
}

const string & Enemy::getName() const {
    return name;
}

const Coord & Enemy::move() {

    bool stun = false;
    double damage;
    attacked = false;
    for( auto spell = spells.begin(); spell != spells.end(); spell++ ) {
        if(*spell == nullptr)
            continue;

        damage = (*spell)->getDamage();
        (**spell).operator--();

        if(damage == 0)
            stun = true;
        else
            attacked = true;

        health -= damage;
        if( (*spell)->getDuration() == 0 ) {
            spells.erase(spell--);
        }
    }
    if(!stun){
        if( pathIndex + speed < static_cast<int>(path.size()) ) {
            position = path[pathIndex + speed];
            pathIndex += speed;
        }
        else {
            position = path[path.size() - 1];
            pathIndex = static_cast<int>(path.size() - 1);
        }
    }
    spells.shrink_to_fit();
    return position;
}

void Enemy::takeDamage(double damage) {
    health -= damage;
    attacked = true;
}

bool Enemy::isDead() const {
    return health <= 0;
}

double Enemy::getHealth() const {
    return health;
}

int Enemy::getReward() const {
    return reward;
}

void Enemy::getSpell( const shared_ptr<Spell> & ptr ) {
    if (ptr->Spell::type() == Spell::SpellType::ERR)
        throw invalid_argument("Invalid spell type");

    if(ptr->Spell::type() == Spell::SpellType::ICE)
    {
        bool found = false;
        for(auto & spell : spells)
        {
            if(spell->type() == Spell::SpellType::ICE)
                found = true;
        }
        if(!found)
            spells.emplace_back(ptr);
    }
    else
        spells.emplace_back(ptr);

}

const Coord & Enemy::getPosition() const {
    return position;
}

void Enemy::printChar() const {
    if (attacked)
        cout << "\033[1;41m" << ch << "\033[0m"; // Red background
    else
        cout << "\033[1;31m" << ch << "\033[0m"; // Red character
}

void Enemy::importSpells(const vector<shared_ptr<Spell>> & spellsT) {
    spells = spellsT;
    if(!spells.empty())
        attacked = true;
}

string Enemy::Export() const {
    string s;
    s+= "Enemy\n";
    s += name + '\n';
    s += to_string(level) + '\n';
    s += to_string(health) + '\n';
    s += to_string(position.x) + '\n';
    s += to_string(position.y) + '\n';
    for (auto & spell : spells) {
        s += spell->Export();

    }

    s += "end\n";
    return s;
}