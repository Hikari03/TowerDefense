#ifndef TOWER_DEFENCE_GAMEUPDATER_H
#define TOWER_DEFENCE_GAMEUPDATER_H

#include "GameState.h"
#include "Minion.h"
#include "Orc.h"
#include "Dragon.h"
#include "Boss.h"
#include "Path.h"

/**
 * @brief Used to update the game state
 */
class GameUpdater {

public:

    explicit GameUpdater(GameState & game);


    /**
     * @brief Updates the game state to next frame
     *
     * @details
     *      - Moves all enemies\n
     *      - Calls attack function for all towers\n
     *      - Checks if any enemy is dead\n
     *      - If any enemy is dead, remove it from the map, enemies vector, and give player money\n
     *      - If any enemy reaches the end, remove it from the map, enemies vector, and remove health\n
     *      - If health is 0, set gameOver to true\n
     *      - If wave == 10 and enemies vector is empty, set gameWon to true
     *
     * @return void
     */
    void update();

    /**
     * @brief Sends new wave of enemies
     *
     * @details
     *      Checks if there is already wave in progress\n
     *      Checks if there is tower built before first wave\n
     *      If there is no wave in progress and there is tower built, sends new wave\n
     *      Sends enemies based on what evaluateDifficulty() returns\n
     *      If wave % 2 == 0, sends boss enemy
     *
     * @calls evaluateDifficulty()
     * @return void
     */
    void sendWave();

    private:


    /**
     * @brief Calculates how much enemies to send and how much difficult they should be
     * @return pair<int, int> - first is level of enemies to send, second is how much enemies to send
     */
    pair<int, int> evaluateDifficulty() const;

    /**
     * @brief Spawns an enemy at the spawn point
     * @param level - level of enemy
     * @param type - type of enemy  1 = minion, 2 = goblin, 3 = dragon, 4 = boss
     */
    void spawnEnemy(int level, int type);

    /**
     * @brief Spawns an enemy at the spawn point
     * @param enemy - enemy to spawn
     */
    void spawnEnemy(shared_ptr<Enemy> & enemy);

    GameState & game;

};


#endif //TOWER_DEFENCE_GAMEUPDATER_H
