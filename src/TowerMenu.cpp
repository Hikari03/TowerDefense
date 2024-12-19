#include <unistd.h>
#include <termios.h>
#include "TowerMenu.h"


TowerMenu::TowerMenu(Renderer & renderer, GameState & game) : renderer(renderer), game(game) {}

void TowerMenu::show() {
    string choiceString;
    struct termios original;

    // save the original terminal settings
    tcgetattr(STDIN_FILENO, &original);
    setRawMode();

    while( true )
    {
        renderer.render(true, choiceString.empty() ? -1 : ( stoul(choiceString)-1 > game.towers.size() ? -1 : stoi(choiceString)-1 )); // render in tower menu mode
        cout << endl << GREEN "Tower spots are ordered from left to right, up to down\n";
        cout << "Total number of tower spots: " << game.towers.size() << "\n";
        cout << "Controls: 'backspace' to erase | 'enter' to confirm\n";
        cout << "Enter number of tower spot you want to edit, leave blank to exit:\033[38;5;165m ";
        cout << choiceString << flush;
        const char towerSpotS = getchar();
        cout << RESET << flush;
        if( towerSpotS == 127 )//backspace
        {
            if( !choiceString.empty() )
                choiceString.pop_back();
            continue;
        }

        else if( towerSpotS == '\n' || towerSpotS == '\r' )//enter
            break;

        else if( towerSpotS < 48 || towerSpotS > 57 )//not a number
            continue;

        else if ( choiceString.length() < 2 )
            choiceString += towerSpotS;
    }

    // reset terminal to original settings
    tcsetattr(STDIN_FILENO, TCSANOW, &original);


    if (choiceString.empty()) {
        renderer.render();
        return;
    }
    long unsigned int towerSpot = stoul(choiceString) ;


    if( towerSpot > game.towers.size() || towerSpot == 0) {
        cout << "\n" RED "Invalid tower spot" RESET << endl;
        sleep(1);
        show();
        return;
    }

    towerSpot--;

    system("clear");

    //stats
    cout << GREEN "Tower stats:\n";
    if(game.towers[towerSpot] == nullptr)
        cout << "No tower\n";
    else
    {
        cout << "Type: ";
        switch (game.towers[towerSpot]->getID())
        {
            case 1:
                cout << "Basic tower";
                break;
            case 2:
                cout << "Fire tower";
                break;
            case 3:
                cout << "Ice tower";
                break;
            case 4:
                cout << "Sniper tower";
                break;

        }
        cout << "\n";

        cout << "Damage: " << game.towers[towerSpot]->getDamage() << "\n";
        cout << "Range: " << game.towers[towerSpot]->getRange() << "\n";
        cout << "Fire rate: Once per " << game.towers[towerSpot]->getCooldown()+1 << " rounds." << "\n";
        cout << "Targeting: " << game.towers[towerSpot]->getTargeting() << "\n";
        cout << "Level: " << game.towers[towerSpot]->getLevel() << "\n";
        cout << "Upgrade cost: " << game.towers[towerSpot]->getUpgradeCost() << "\n";
        cout << "Sell value: " << game.towers[towerSpot]->getSellPrice() << "\n";
    }
    cout << "----------------------------------------------" RESET << "\n";

    cout << "\n" GREEN "Do you want to:\n";
    cout << "1. Buy tower\n";
    cout << "2. Upgrade tower\n";
    cout << "3. Change tower targeting\n";
    cout << "4. Sell tower\n";
    cout << "5. Exit\n";
    cout << "Enter your choice:\033[38;5;165m " << flush;
    char choice;
    system("/bin/stty raw");
    cin >> choice;
    system("/bin/stty cooked");
    cout << RESET << flush;

    switch(choice) {
        case '1':
            buyTower(towerSpot, game.towerSpots[towerSpot]);
            break;
        case '2':
            upgradeTower(towerSpot);
            break;
        case '3':
            setTargeting(towerSpot);
            break;
        case '4':
            sellTower(towerSpot);
            break;
        case '5':
            break;
        default:
            cout << RED "Invalid choice" RESET << endl;
            sleep(1);
            show();
            break;
    }
    renderer.render();

}

void TowerMenu::buyTower(unsigned long pos, Coord & position) {
    if(game.towers[pos] != nullptr) {
        cout << "\n" RED "There is already a tower on this spot" RESET << endl;
        sleep(1);
        return;
    }

    else if(game.money < game.config.towerCost) {
        cout << "\n" RED "Not enough money" RESET << endl;
        sleep(1);
        return;
    }

    else {
        game.money -= game.config.towerCost;
        game.towers[pos] = make_shared<Tower>(make_shared<TargetingClosest>(),position, game.config);
        game.map[game.towerSpots[pos].x][game.towerSpots[pos].y] = game.towers[pos];
        return;
    }

}

void TowerMenu::upgradeTower(unsigned long pos) {
    if(game.towers[pos] == nullptr) {
        cout << "\n" RED "There is no tower on this spot" RESET << endl;
        sleep(1);
        return;
    }



    cout << "\n" GREEN "Do you want to upgrade or specialize? (u/s):\033[38;5;165m " << flush;
    char choice;
    system("/bin/stty raw");
    cin >> choice;
    system("/bin/stty cooked");
    cout << RESET << flush;


    if(choice == 'u') {
        if(game.towers[pos]->getLevel() >= game.config.towerMaxLevel) {
            cout << "\n" RED "Tower is already at max level" RESET << endl;
            sleep(1);
            return;
        }

        else if(game.money < game.towers[pos]->getUpgradeCost()) {
            cout << "\n" RED "Not enough money" RESET << endl;
            sleep(1);
            return;
        }

        else {
            game.money -= game.towers[pos]->getUpgradeCost();
            game.towers[pos]->upgrade();
            cout << "\n" GREEN "Tower upgraded" RESET << endl;
            sleep(1);
            return;
        }
    }

    else if(choice == 's') {

        if(game.towers[pos]->getID() > 1)
        {
            cout << "\n" RED "Tower is already specialized" RESET << endl;
            sleep(1);
            return;
        }

        else

        if(game.money < game.towers[pos]->getUpgradeCost()) {
            cout << "\n" RED "Not enough money" RESET << endl;
            sleep(1);
            return;
        }

        else {
            game.money -= game.towers[pos]->getUpgradeCost();

            system("clear");
            cout << GREEN "Do you want to specialize to:\n";
            cout << "1. Fire\n";
            cout << "2. Ice\n";
            cout << "3. Sniper\n";
            cout << "Enter your choice:\033[38;5;165m " << flush;
            system("/bin/stty raw");
            cin >> choice;
            system("/bin/stty cooked");
            cout << RESET << flush;

            switch(choice) {
                case '1':
                    game.towers[pos] = make_shared<FireTower>(*game.towers[pos]);
                    break;
                case '2':
                    game.towers[pos] = make_shared<IceTower>(*game.towers[pos]);
                    break;
                case '3':
                    game.towers[pos] = make_shared<SniperTower>(*game.towers[pos]);
                    break;
                default:
                    cout << "\n" RED "Invalid choice:\033[2;31m "<< choice << RESET << endl;
                    sleep(1);
                    return;
            }
            game.map[game.towerSpots[pos].x][game.towerSpots[pos].y] = game.towers[pos];
        }
    }

    else {
        cout << "\n" RED "Invalid choice: \033[2;31m" << choice << RESET << endl;
        sleep(1);
        return;
    }

}

void TowerMenu::setTargeting(unsigned long pos) {
    if(game.towers[pos] == nullptr) {
        cout << "\n" RED "There is no tower on this spot" RESET << endl;
        sleep(1);
        return;
    }

    cout << "\n" GREEN "Current targeting: "
            << game.towers[pos]->getTargeting()
            << endl;
    cout << "What do you want to change it to?" << endl;
    cout << "1. Closest" << endl;
    cout << "2. Farthest" << endl;
    cout << "3. Strongest" << endl;
    cout << "Type your choice:\033[38;5;165m " << flush;

    char choice;
    system("/bin/stty raw");
    cin >> choice;
    system("/bin/stty cooked");
    cout << RESET << flush;

    switch(choice) {
        case '1':
            game.towers[pos]->setTargeting(make_shared<TargetingClosest>());
            break;
        case '2':
            game.towers[pos]->setTargeting(make_shared<TargetingFarthest>());
            break;
        case '3':
            game.towers[pos]->setTargeting(make_shared<TargetingStrongest>());
            break;
        default:
            cout << "\n" RED "Invalid choice" RESET << endl;
            sleep(1);
            return;
    }
    cout << "\n" GREEN "Targeting changed" RESET << endl;
    sleep(1);
}

void TowerMenu::sellTower(unsigned long pos) {
    if(game.towers[pos] == nullptr) {
        cout << "" RED "\nThere is no tower on this spot" RESET << endl;
        sleep(2);
        return;
    }

    else {
        cout << GREEN "\nAre you sure you want to sell this tower? You are going to get " << game.towers[pos]->getSellPrice() <<" money (y/N):\033[38;5;165m " << flush;
        system("/bin/stty raw");
        char choice;
        cin >> choice;
        system("/bin/stty cooked");
        cout << RESET << flush;
        if(choice != 'y') {
            return;
        }

        if((game.money + game.towers[pos]->sell()) < 0 ) {
            cout << "\n" RED "You have too much money, so you will not get any >:)" RESET << endl;
            sleep(1);
        }
        else
            game.money += game.towers[pos]->sell();

        game.map[game.towerSpots[pos].x][game.towerSpots[pos].y] = make_shared<FreeTowerSpot>();
        game.towers[pos] = nullptr;
        cout << GREEN "\nTower sold" RESET << endl;
        sleep(1);
        return;
    }

}

void TowerMenu::setRawMode() {
    struct termios newt;

    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &newt);

    // Disable echo and input canonicalization
    newt.c_lflag &= ~(ICANON | ECHO);

    // Set the modified attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}





