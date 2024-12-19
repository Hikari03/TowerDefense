#ifndef TOWER_DEFENCE_TOWERMENU_H
#define TOWER_DEFENCE_TOWERMENU_H

#include "Renderer.h"
#include "TargetingClosest.h"
#include "TargetingFarthest.h"
#include "TargetingStrongest.h"
#include "FreeTowerSpot.h"
#include "FireTower.h"
#include "IceTower.h"
#include "SniperTower.h"

/**
 * @brief Shows tower menu
 *
 * @details
 *      Used for selection of tower spot and tower spot editing\n
 *      Tower spot editing includes buying, upgrading, changing targeting and selling towers
 */
class TowerMenu {

public:

    TowerMenu(Renderer & renderer, GameState & game);

    void show();

private:

    /**
     * @brief Buys tower on selected tower spot
     *
     * @details
     *      Checks if there is enough money and if there is no tower on selected spot\n
     *      If there is enough money and no tower, buys tower and places it on map
     *
     * @param pos - position of tower in towers vector
     * @param position - position of tower on map
     * @return void
     */
    void buyTower(long unsigned int pos, Coord & position);

    /**
     * @brief Upgrades tower on selected tower spot
     *
     * @details
     *      User can choose between upgrading and specializing tower\n
     *      Checks if there is tower on selected spot\n
     *      If there is tower, checks if tower is at max level and if there is enough money\n
     *      If tower is not at max level and there is enough money, upgrades tower\n
     *
     * @param pos - position of tower in towers vector
     * @return void
     */
    void upgradeTower(long unsigned int pos);

    /**
     * @brief Sets targeting of tower on selected tower spot
     *
     * @details
     *      Checks if there is tower on selected spot\n
     *      If there is tower, asks user what he wants to change targeting to\n
     *      If user chooses valid option, changes targeting
     *
     * @param pos
     * @return void
     */
    void setTargeting(long unsigned int pos);

    /**
     * @brief Sells tower on selected tower spot
     *
     * @details
     *      Checks if there is tower on selected spot\n
     *      If there is tower, asks user if he is sure he wants to sell tower\n
     *      If user is sure, sells tower and adds money to player
     *
     * @param pos - position of tower in towers vector
     * @return void
     */
    void sellTower(long unsigned int pos);

    /**
    * @brief sets raw mode for terminal with no echo
    */
    void setRawMode();

    Renderer & renderer;
    GameState & game;

};


#endif //TOWER_DEFENCE_TOWERMENU_H
