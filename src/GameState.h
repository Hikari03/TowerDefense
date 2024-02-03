#ifndef TOWER_DEFENCE_GAMESTATE_H
#define TOWER_DEFENCE_GAMESTATE_H


#include <vector>
#include <memory>
#include "Tile.h"
#include "Tower.h"
#include "Enemy.h"
#include "ConfigHolder.h"
#include "Coord.h"

#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define SELECTED_TOWER_SPOT "\033[48;5;201m"
#define UNSELECTED_TOWER_SPOT "\033[48;5;219m"
#define SELECTED_TOWER "\033[48;5;57m"
#define UNSELECTED_TOWER "\033[48;5;99m"

#define RESET "\033[0m"

using namespace std;

/**
 * @brief Stores all information about the game.
 */
class GameState {
public:
    GameState() = default;
    ~GameState() = default;
    GameState(const GameState & other) = default;


    int money = 0;
    int wave = 0;
    int enemiesLeft = 0;
    int enemiesKilled = 0;
    int health = 0;
    int score = 0;

    vector<vector<shared_ptr<Tile>>> map; /**< 2D vector of tiles for rendering */
    vector<shared_ptr<Tower>> towers; /**< ordered by position */
    vector<shared_ptr<Enemy>> enemies; /**< ordered by position */
    vector<shared_ptr<Enemy>> enemiesToSpawn;
    vector<Coord> towerSpots; /**< ordered by position */
    vector<Coord> path; /**< holds path from spawn point to end point */
    Coord spawnPoint;
    Coord endPoint;
    bool gameOver = false;
    ConfigHolder config;


};


#endif //TOWER_DEFENCE_GAMESTATE_H
