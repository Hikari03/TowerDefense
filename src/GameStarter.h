#ifndef TOWER_DEFENCE_GAMESTARTER_H
#define TOWER_DEFENCE_GAMESTARTER_H

#define ASSETS_PATH "assets/"
#define UI_FILE "assets/UI.txt"
#define CONFIG_FILE "assets/config.txt"
#define SAVE_FILE "assets/save.txt"
#define SAVE_FILE_CLEAR R"(echo "\n" > ./assets/save.txt)"

#include "GameState.h"
#include "Path.h"
#include "FreeTowerSpot.h"
#include "Wall.h"
#include "Character.h"
#include "BFS.h"

/**
 * @brief Handles preparation of the game
 * @details
 *      Loads UI, map and config file
 */
class GameStarter {

public:
    GameStarter() = default;

    /**
     * @brief Loads UI, map and config file
     *
     * @details
     *      Loads config file from there loads map and other settings\n
     *      Loads UI from UI.txt file\n
     *      Goes through map and creates tiles based on characters in map\n
     *      Registers tower spots, spawn point and end point
     *
     * @throws runtime_error if any file is not found or has wrong format
     */
    void prepareGame(GameState & game);

private:

    /**
     * @brief Loads config file
     * @return string - map file location
     */
    string loadConfig(ifstream & configFile, GameState & game);

    /**
     * @brief Calculates path for enemies
     * @return void
     */
    void generateBFSMap(GameState & game);

    /**
     * @brief trims string for parsing
     * @param stream
     * @param pos where to start parsing
     * @param keepChars if true, keeps chars in string
     * @return
     */
    string getAndParse(ifstream & stream, int pos, bool keepChars = false);
};


#endif //TOWER_DEFENCE_GAMESTARTER_H
