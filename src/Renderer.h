#ifndef TOWER_DEFENCE_RENDERER_H
#define TOWER_DEFENCE_RENDERER_H


#include "GameState.h"
#include "Character.h"

/**
 * @brief Class used for rendering the game
 */
class Renderer {

public:
    explicit Renderer(GameState & game);

    /**
     * @brief Renders the game
     *
     * @details
     *      Renders the current state of game on the screen\n
     *      That includes the UI, map, stats and details about enemies\n
     *      Also prepares game for next user input
     *
     * @param towerMenu if true, tower spots will have colored background
     */
    void render (bool towerMenu = false, int towPos = -1) const;

private:
    GameState & game;

};


#endif //TOWER_DEFENCE_RENDERER_H
