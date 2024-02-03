#ifndef TOWER_DEFENCE_SAVEFILEHANDLER_H
#define TOWER_DEFENCE_SAVEFILEHANDLER_H

#define ASSETS_PATH "assets/"
#define UI_FILE "assets/UI.txt"
#define CONFIG_FILE "assets/config.txt"
#define SAVE_FILE "assets/save.txt"
#define SAVE_FILE_CLEAR R"(echo "\n" > ./assets/save.txt)"

#include "GameState.h"
#include "TargetingClosest.h"
#include "TargetingStrongest.h"
#include "TargetingFarthest.h"
#include "IceTower.h"
#include "SniperTower.h"
#include "FireTower.h"
#include "Minion.h"
#include "Orc.h"
#include "Dragon.h"
#include "Boss.h"

/**
 * @brief Handles saving and loading game state to and from file
 */
class SaveFileHandler {

public:

    explicit SaveFileHandler(GameState & game);

    /**
     * @brief Saves game state to file
     *
     * @details
     *      Opens save.txt file\n
     *      If file is not open, prints error message and returns false\n
     *      Saves current map to file\n
     *      Saves money, wave, health, enemiesKilled and enemiesLeft to file\n
     *      Saves towers to file\n
     *      Saves enemies to file\n
     *      Closes file\n
     *      Returns true if save was successful, false otherwise
     *
     * @return bool - true if save was successful, false otherwise
     * @throws invalid_argument if config file is corrupted
     */
    void saveGameState() const;

    /**
     * @brief Loads game state from file
     *
     * @details
     *      Opens save.txt file\n
     *      If file is not open, prints error message and returns\n
     *      Loads money, wave, health, enemiesKilled and enemiesLeft from file\n
     *      Loads towers from file\n
     *      Loads enemies from file\n
     *      Closes file\n
     *
     * @return void
     * @throws invalid_argument if save file or config file is corrupted and if we are loading save for different map
     */
    void loadGameState();


private:
    GameState & game;
};


#endif //TOWER_DEFENCE_SAVEFILEHANDLER_H
