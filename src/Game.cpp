#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "Game.h"

using namespace std;

Game::Game() : game(), starter(), renderer(game), towerMenu(renderer, game), saveFileHandler(game), updater(game) {}

void Game::start() {
    showMainMenu();

}

void Game::showMainMenu() {
    system("clear");
    cout << "\033[1;32m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
                      "┃                                                                                             ┃\n"
                      "┃          ███╗   ███╗ █████╗ ██╗███╗   ██╗    ███╗   ███╗███████╗███╗   ██╗██╗   ██╗         ┃\n"
                      "┃          ████╗ ████║██╔══██╗██║████╗  ██║    ████╗ ████║██╔════╝████╗  ██║██║   ██║         ┃\n"
                      "┃          ██╔████╔██║███████║██║██╔██╗ ██║    ██╔████╔██║█████╗  ██╔██╗ ██║██║   ██║         ┃\n"
                      "┃          ██║╚██╔╝██║██╔══██║██║██║╚██╗██║    ██║╚██╔╝██║██╔══╝  ██║╚██╗██║██║   ██║         ┃\n"
                      "┃          ██║ ╚═╝ ██║██║  ██║██║██║ ╚████║    ██║ ╚═╝ ██║███████╗██║ ╚████║╚██████╔╝         ┃\n"
                      "┃          ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝    ╚═╝     ╚═╝╚══════╝╚═╝  ╚═══╝ ╚═════╝          ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                      ┏━━━━━━━━━━━━━━━┓                                      ┃\n"
                      "┃                                      ┃ 1. Start Game ┃                                      ┃\n"
                      "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ 2. Load Save  ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
                      "┃                                      ┃ 3. Quit Game  ┃                                      ┃\n"
                      "┃                                      ┗━━━━━━━━━━━━━━━┛                                      ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┃                                                                                             ┃\n"
                      "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\033[0m\n" << endl;

    cout << "\nPlease enter your choice: ";

    char choice;
    system("/bin/stty raw");
    cin >> choice;
    system("/bin/stty cooked");

    cout << endl;
    switch (choice) {
        case '1':
            cout << "Starting game..." << endl;
            startGame();
            showMainMenu();
            break;

        case '2':
            cout << "Loading save..." << endl;
            loadSave();
            showMainMenu();
            break;

        case '3':
            cout << "Quitting game..." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            showMainMenu();
            break;
    }
}

void Game::loadSave() {

    try{
        game = GameState();
        starter.prepareGame(game);
        saveFileHandler.loadGameState();
    } catch (exception & e) {
        cout << "When starting game, this error occurred: " << e.what() << endl;
        string error = e.what();
        if(error == "stoi")
            cout << "Please check your config file, unexpected character." << endl;
        sleep(3);
        return;
    }
    runGame();

}

void Game::runGame()
{

    renderer.render();
    char userInput;
    while (game.wave <= 10) {

        cout << "\033[38;5;165m";
        system("/bin/stty raw");
        cin >> userInput;
        system("/bin/stty cooked");
        cout << "\033[0m" << flush;

        switch (userInput) {
            case 'n':
                updater.update();
                renderer.render();
                break;

            case 't':
                towerMenu.show();
                break;

            case 'd':
                debugMenu();
                renderer.render();
                break;

            case 's':
                try{ saveFileHandler.saveGameState(); }
                catch (exception & e) {
                    cout << "\n\033[1;31mError saving game: " << e.what() << "\033[0m" << endl;
                    sleep(1);
                    renderer.render();
                    continue;
                }
                cout << "\n\033[1;32mGame saved.\033[0m" << endl;
                sleep(1);
                renderer.render();
                break;

            case 'v':
                updater.sendWave();
                renderer.render();
                break;

            case 'e':
                return;

            default:
                renderer.render();
                continue;
        }


        if (game.gameOver) {
            printLose();
            return;
        }
    }

    printWin();

}

void Game::startGame() {

    try {
        game = GameState();
        starter.prepareGame(game);
    }
    catch (exception & e) {
        cout << "When starting game, this error occurred: " << e.what() << endl;
        string error = e.what();
        if(error == "stoi")
            cout << "Please check your config file, unexpected character." << endl;
        sleep(3);
        return;
    }

    runGame();
}

void Game::debugMenu() {
    system("clear");

    cout << "1. Add money" << endl;
    cout << "2. Add health" << endl;
    cout << "3. Test BFS" << endl;
    cout << "4. Win" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
    char choice;
    system("/bin/stty raw");
    cin >> choice;
    system("/bin/stty cooked");

    switch(choice) {
        case '1':
            game.money += 1000;
            break;
        case '2':
            game.health += 100;
            break;
        case '3':
            testBFS();
            break;
        case '4':
            game.wave = 10;
            break;
        case '5':
            return;
        default:
            cout << "Invalid choice" << endl;
            sleep(1);
            debugMenu();
            break;
    }
    system("clear");
}

void Game::testBFS() {
    system("clear");
    BFS bfs(game.map);
    //bfs.printMap();
    sleep(2);
    vector <Coord> path1 = bfs(game.spawnPoint, game.endPoint);
    bfs.printMapWithPath(path1);
    cin.get();
}

void Game::printLose() const {

    cout << "\n\n\n" << endl;
    system("clear");
    cout << GREEN <<
            "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
            "┃                                                                                             ┃\n"
            "┃              ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗      ██████╗ ███████╗███████╗               ┃\n"
            "┃              ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║     ██╔═══██╗██╔════╝██╔════╝               ┃\n"
            "┃               ╚████╔╝ ██║   ██║██║   ██║    ██║     ██║   ██║███████╗█████╗                 ┃\n"
            "┃                ╚██╔╝  ██║   ██║██║   ██║    ██║     ██║   ██║╚════██║██╔══╝                 ┃\n"
            "┃                 ██║   ╚██████╔╝╚██████╔╝    ███████╗╚██████╔╝███████║███████╗               ┃\n"
            "┃                 ╚═╝    ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝ ╚══════╝╚══════╝               ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                               ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                                ┃\n"
            "┃                               ┃ Stats:                     ┃                                ┃\n"
            "┃                               ┃" << printScore() <<       "┃                                ┃\n"
            "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << printHealth() <<      "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
            "┃                               ┃" << printWave() <<        "┃                                ┃\n"
            "┃                               ┃" << printMoney() <<       "┃                                ┃\n"
            "┃                               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                                ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                   Press any key to exit                                     ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
            << RESET << endl;

    char c;
    system("/bin/stty raw");
    cin >> c;
    system("/bin/stty cooked");
}

void Game::printWin() const {
    cout << "\n\n\n" << endl;
    system("clear");
    cout << GREEN <<
            "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
            "┃                                                                                             ┃\n"
            "┃                   ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗                    ┃\n"
            "┃                   ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║                    ┃\n"
            "┃                    ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║                    ┃\n"
            "┃                     ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║                    ┃\n"
            "┃                      ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║                    ┃\n"
            "┃                      ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝                    ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                               ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓                                ┃\n"
            "┃                               ┃ Stats:                     ┃                                ┃\n"
            "┃                               ┃" << printScore() <<       "┃                                ┃\n"
            "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫" << printHealth() <<      "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
            "┃                               ┃" << printWave() <<        "┃                                ┃\n"
            "┃                               ┃" << printMoney() <<       "┃                                ┃\n"
            "┃                               ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛                                ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                   Press any key to exit                                     ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┃                                                                                             ┃\n"
            "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n"
            << RESET << endl;

    char c;
    system("/bin/stty raw");
    cin >> c;
    system("/bin/stty cooked");

}

string Game::printScore() const {
    string scoreS = " Score: ";
    scoreS += to_string(game.score);
    while (scoreS.length() < 28) { // width of the box in printWin/Lose
        scoreS += " ";
    }
    return scoreS;
}

string Game::printHealth() const {
    string healthS = " Health: ";
    healthS += to_string(game.health);
    while (healthS.length() < 28) {// width of the box in printWin/Lose
        healthS += " ";
    }
    return healthS;
}

string Game::printWave() const {
    string waveS = " Wave: ";
    waveS += to_string(game.wave);
    while (waveS.length() < 28) {// width of the box in printWin/Lose
        waveS += " ";
    }
    return waveS;
}

string Game::printMoney() const {
    string moneyS = " Money: ";
    moneyS += to_string(game.money);
    while (moneyS.length() < 28) {// width of the box in printWin/Lose
        moneyS += " ";
    }
    return moneyS;
}