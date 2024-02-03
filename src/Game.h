#ifndef TOWER_DEFENCE_GAME_H
#define TOWER_DEFENCE_GAME_H

#include "GameState.h"
#include "SaveFileHandler.h"
#include "GameStarter.h"
#include "Renderer.h"
#include "TowerMenu.h"
#include "GameUpdater.h"

/**
 * @brief Main class that runs the game
 * @details
 *      Holds all objects needed to run the game\n
 *      Starts the game
 *
 */
class Game {
public:

    Game();
    ~Game() = default;
    Game(const Game & other) = delete;

    void start();

private:

    /**
     * @brief Shows main menu
     */
    void showMainMenu();

    /**
     * @brief Loads save file and starts the game
     */
    void loadSave();

    /**
     * @brief Runs the game
     *
     * @details
     *      Renders the game\n
     *      Gets user input\n
     *      Updates game based on user input\n
     *      Renders the game again\n
     *      Repeats until wave 10 is reached
     *
     * @param game
     */
    void runGame();

    /**
     * @brief Starts new game
     */
    void startGame();

    /**
     * @brief Displays debug menu
     */
    void debugMenu();

    /**
     * @brief Tests BFS algorithm and prints result - DEBUG
     */
    void testBFS();

    /**
     * @brief Renders the lose screen with stats
     */
    void printLose() const;

    /**
     * @brief Renders the win screen with stats
     */
    void printWin() const;

    /**
     * @brief Returns a string with the score padded to 28 characters
     *
     * @return string with score
     */
    string printScore() const;

    /**
     * @brief Returns a string with the health padded to 28 characters
     * @return string with health
     */
    string printHealth() const;

    /**
     * @brief Returns a string with the money padded to 28 characters
     * @return string with money
     */
    string printMoney() const;

    /**
     * @brief Returns a string with the wave padded to 28 characters
     * @return string with wave
     */
    string printWave() const;

    GameState game;
    GameStarter starter;
    Renderer renderer;
    TowerMenu towerMenu;
    SaveFileHandler saveFileHandler;
    GameUpdater updater;

};


#endif //TOWER_DEFENCE_GAME_H
