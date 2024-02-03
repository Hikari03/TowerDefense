#ifndef TOWER_DEFENCE_TOWER_H
#define TOWER_DEFENCE_TOWER_H

#include "Tile.h"
#include "Enemy.h"
#include "ConfigHolder.h"
#include "Targeting.h"

/**
 * @brief Class representing tower
 * @details
 *      Has id, level, damage, range, cooldown, upgradeCost, sellPrice, towerTargeting, position\n
 *      Inherited from Tile\n
 *      Inherited by FireTower, IceTower, SniperTower that override some methods and add some attributes
 */
class Tower : public Tile {
public:

    Tower(shared_ptr<Targeting> towerTargeting ,Coord & position, ConfigHolder & config);

    /*
     * Constructor for loading from save
     */
    Tower(int level, double damage, int range, int cooldown, int pendingCooldown,
          int upgradeCost, int sellPrice, shared_ptr<Targeting> towerTargeting, Coord & position, ConfigHolder & config);

    Tower(const Tower & other) = default;

    void printChar() const override;


    virtual void upgrade();

    int sell();

    double getDamage() const;

    int getRange() const;

    int getCooldown() const;

    int getLevel() const;

    int getUpgradeCost() const;

    int getSellPrice() const;

    const Coord & getPosition() const;

    int getID() const;

    /**
     * @brief Attacks enemy
     *
     * @details
     *      Goes through enemies and finds the one to attack depending on targeting mode\n
     *      If enemy is in range, damages it and returns pointer to it\n
     *      If no enemy is in range, returns nullptr\n\n
     *      If tower is fire or ice tower, overridden method that casts corresponding spell is called instead
     *
     *
     * @param enemies - vector of enemies
     * @return shared_ptr<Enemy> - pointer to attacked enemy or nullptr
     */
    virtual shared_ptr<Enemy> attack(vector<shared_ptr<Enemy>> & enemies);

    /*
     * sets targeting mode
     */
    void setTargeting(shared_ptr<Targeting> targeting);

    const string & getTargeting() const;

    /**
     * @brief Exports tower to string
     *
     * @details
     *      Exports tower to string in format:\n
     *      id level damage range cooldown upgradeCost sellPrice towerTargeting positionX positionY\n
     *      If tower is fire tower overridden method is called that adds intensity to the end of string
     * @return
     */
    virtual string Export() const;


protected:
    int id;
    int level;
    double damage;
    int range;
    int cooldown;
    int pendingCooldown = 0;
    int upgradeCost;
    int sellPrice;
    shared_ptr<Targeting> towerTargeting;
    Coord position;

    ConfigHolder & config;


};

#endif //TOWER_DEFENCE_TOWER_H
