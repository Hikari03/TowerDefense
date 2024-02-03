#include "Renderer.h"

Renderer::Renderer(GameState & game) : game(game) {}

void Renderer::render (bool towerMenu, int towPos) const {

    system("clear");

    string tmpMoney = to_string(game.money) + ' ';
    string tmpWave = to_string(game.wave) + ' ';
    string tmpEnemiesLeft = to_string(game.enemiesLeft) + ' ';
    string tmpEnemiesKilled = to_string(game.enemiesKilled) + ' ';
    string tmpHealth = to_string(game.health) + ' ';

    int posX = 78; // x coordinate of the first counter in box
    int posY = 1; // y coordinate of the first counter in box

    // print out counters

    for (unsigned long i = 0; i < tmpMoney.length(); i++) {
        game.map[posY][posX + i] = make_shared<Character>(tmpMoney[i]);
    }

    ++posY; // next line

    for (unsigned long i = 0; i < tmpWave.length(); i++) {
        game.map[posY][posX + i] = make_shared<Character>(tmpWave[i]);
    }

    ++posY;

    for (unsigned long i = 0; i < tmpHealth.length(); i++) {
        game.map[posY][posX + i] = make_shared<Character>(tmpHealth[i]);
    }

    ++posY;

    for (unsigned long i = 0; i < tmpEnemiesLeft.length(); i++) {
        game.map[posY][posX + i] = make_shared<Character>(tmpEnemiesLeft[i]);
    }

    ++posY;

    for (unsigned long i = 0; i < tmpEnemiesKilled.length(); i++) {
        game.map[posY][posX + i] = make_shared<Character>(tmpEnemiesKilled[i]);
    }

    // print out enemies
    posX = 2; // x coordinate of the first enemy name in box
    posY = 19; // y coordinate of the first enemy name in box
    string tmpName;

    //clear the enemy names
    for (unsigned long line = 19; line < 25; line++) { // 25 is the last line of the box
        for (unsigned long col = 2; col < 30; col++) { // 30 is the last column of the first box
            game.map[line][col]->setChar(' ');
        }
    }
    for (unsigned long line = 19; line < 25; line++) { // 25 is the last line of the box
        for (unsigned long col = 32; col < 60; col++) { // 60 is the last column of the second box
            game.map[line][col]->setChar(' ');
        }
    }


    unsigned long j, i;

    for (const auto & enemy : game.enemies) {
        tmpName = enemy->getName();
        for(i = 0; i < tmpName.length(); i++) {
            game.map[posY][posX + i] = make_shared<Character>(tmpName[i]);
        }

        // print out health
        string tmpEnHealth = to_string(enemy->getHealth());
        for(j = 0; j < tmpEnHealth.length()-3; j++) { // -3 for cropping
            game.map[posY][posX + i + j + 2] = make_shared<Character>(tmpEnHealth[j]);
        }
        while(game.map[posY][posX + i + j]->getChar() != "┃" && game.map[posY][posX + i + j]->getChar() != "┣") {
            game.map[posY][posX + i + j++]->setChar(' ');
        }

        posY++;

        if(posY > 24) { // if the box is full, start printing in the second box
            posY = 19; // y coordinate of the first enemy name the second box
            posX = 32; // x coordinate of the first enemy name the second box
        }
    }

    for (unsigned long line = 0; line < game.map.size(); line++) {
        for (unsigned long col = 0; col < game.map[line].size(); col++) {
            //############################################################### TOWER MENU
            if(towerMenu)
            {
                if(game.map[line][col]->type() == Tile::Type::FREE_TOWER_SPOT)
                    if(towPos != -1) {
                        if (game.towerSpots[towPos] == Coord(static_cast<int>(line), static_cast<int>(col))) // check if tower spot is selected
                            cout << SELECTED_TOWER_SPOT << game.map[line][col]->getChar() << RESET;
                        else
                            cout << UNSELECTED_TOWER_SPOT << game.map[line][col]->getChar() << RESET;
                    }
                    else
                        cout << UNSELECTED_TOWER_SPOT << game.map[line][col]->getChar() << RESET;

                else if(game.map[line][col]->type() == Tile::Type::TOWER)
                {
                    if(towPos != -1 && game.towers[towPos] != nullptr) {
                        if (game.towers[towPos]->getPosition() == Coord(static_cast<int>(line), static_cast<int>(col))) // check if tower is selected
                            cout << SELECTED_TOWER << game.map[line][col]->getChar() << RESET;
                        else
                            cout << UNSELECTED_TOWER << game.map[line][col]->getChar() << RESET;
                    }
                    else
                        cout << UNSELECTED_TOWER << game.map[line][col]->getChar() << RESET;
                }
                else
                    game.map[line][col]->printChar();
            }
            //################################################################### NORMAL

            else
                game.map[line][col]->printChar();
        }

        if(line < game.map.size()-1) {
            cout << "\n";
        }
    }
    cout << " " << flush;

}

