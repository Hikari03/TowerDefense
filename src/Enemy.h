#ifndef TOWER_DEFENCE_ENEMY_H
#define TOWER_DEFENCE_ENEMY_H


#include <vector>
#include <memory>
#include "Tile.h"
#include "Spell.h"
#include "Coord.h"
#include "ConfigHolder.h"

/**
 * @brief This class is the base class for all enemies
 */
class Enemy : public Tile {

public:

    /*
     * Constructor for loading from save
     */
    Enemy(int lvl, Coord & position, ConfigHolder & config);

    Enemy(const Enemy & other);

    /**
     * @brief Imports path for enemy to follow
     * @param path
     */
    void importPath(const vector<Coord> & path);

    /**
     * @brief Syncs position with path
     * @details Finds index of current position in path
     */
    void syncPosition();

    const string & getName() const;

    void printChar() const override;

    /**
     * @brief Moves enemy
     * @details
     *      Moves enemy to next position in path and applies spells
     *
     * @return Position of enemy
     */
    virtual const Coord & move();

    /**
     * @brief Applies damage to enemy
     * @details
     *      If enemy is armored (Orc) takes less damage
     *      If enemy is currently invisible (Dragon) takes no damage
     * @param damage
     */
    virtual void takeDamage(double damage);

    bool isDead() const;

    double getHealth() const;

    int getReward() const;

    const Coord & getPosition() const;

    /**
     * @brief Applies spell to enemy
     * @param ptr - pointer to spell
     */
    void getSpell(const shared_ptr<Spell> & ptr); // (fire, ice)

    void importSpells(const vector<shared_ptr<Spell>> & spells);

    /**
     * @brief Exports enemy to save
     * @return
     */
    virtual string Export() const;

protected:
    string name = "err";
    bool attacked = false;
    double maxHealth = 0;
    double health = 0;
    int reward = 0;
    int level = 0;
    Coord position;
    vector<Coord> path;
    int pathIndex = 0;
    vector<shared_ptr<Spell>> spells; // (fire, ice)
    ConfigHolder & config;
    int speed;

};
#endif //TOWER_DEFENCE_ENEMY_H
