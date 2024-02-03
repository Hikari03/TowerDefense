#include <fstream>
#include <algorithm>
#include "SaveFileHandler.h"

SaveFileHandler::SaveFileHandler(GameState & game) : game(game) {}

void SaveFileHandler::saveGameState() const {


    system(SAVE_FILE_CLEAR);
    ofstream saveFile(SAVE_FILE);
    if(!saveFile.is_open()) {
        throw runtime_error("Error opening config file");
    }

    string configMapName;

    ifstream configFile(CONFIG_FILE);
    if(!configFile.is_open()) {
        throw runtime_error("Error opening config file");
    }
    getline(configFile, configMapName);
    configFile.close();
    configMapName.erase(remove_if(configMapName.begin(), configMapName.end(), ::isspace), configMapName.end());
    configMapName = configMapName.substr(4);

    saveFile << configMapName << endl;

    saveFile << game.money << endl;
    saveFile << game.wave << endl;
    saveFile << game.health << endl;
    saveFile << game.enemiesKilled << endl;
    saveFile << game.enemiesLeft << endl;

    int NOfTowers = game.towerSpots.size();

    // export towers
    for(const auto &tower : game.towers) {
        if(tower == nullptr) {
            saveFile << "0" << endl;
        }
        else {
            saveFile << tower->Export();
        }
        NOfTowers--;
        if(NOfTowers == 0) {
            break;
        }
    }
    saveFile << "---" << endl;

    // export enemies
    for(const auto &enemy : game.enemies) {
        if(enemy == nullptr) {
            saveFile << "0" << endl;
        }
        else {
            saveFile << enemy->Export();
        }
    }

    saveFile << "---" << endl;

    //export enemies to spawn
    for(const auto &enemy : game.enemiesToSpawn) {
        if(enemy == nullptr) {
            saveFile << "0" << endl;
        }
        else {
            saveFile << enemy->Export();
        }
    }


    saveFile.close();
}

void SaveFileHandler::loadGameState() {

    ifstream saveFile(SAVE_FILE);
    if(!saveFile.is_open()) {
        throw runtime_error("Error opening save file");
        return;
    }
    cout << "Getting save data" << endl;

    string line, configMapName;

    // check if map in config is the same as the one in the save file
    ifstream configFile(CONFIG_FILE);
    if(!configFile.is_open()) {
        throw runtime_error("Error opening config file");
    }
    getline(configFile, configMapName);
    configFile.close();
    configMapName.erase(remove_if(configMapName.begin(), configMapName.end(), ::isspace), configMapName.end());
    configMapName = configMapName.substr(4);

    getline(saveFile, line);
    if(line != configMapName) {
        throw runtime_error("Save file is not compatible with the current map");
    }

    getline(saveFile, line);
    game.money = stoi(line);
    getline(saveFile, line);
    game.wave = stoi(line);
    getline(saveFile, line);
    game.health = stoi(line);
    getline(saveFile, line);
    game.enemiesKilled = stoi(line);
    getline(saveFile, line);
    game.enemiesLeft = stoi(line);

    int lineNum;

    cout << "Loading towers" << endl;
    // Load towers
    int id = 0;
    int level = 0;
    double damage = 0;
    int range = 0;
    int cooldown = 0;
    int pendingCooldown = 0;
    int upgradeCost = 0;
    int sellPrice = 0;
    string towerTargeting;
    int positionX = 0;
    int positionY = 0;
    int intensity = 0;

    // Load towers
    long unsigned int towerSpot = 0;
    while(true) {
        if(towerSpot > game.towerSpots.size()-1)
            break;
        lineNum = 0;
        getline(saveFile, line);
        cout << line << endl;
        if(line == "0") {
        }
        else {
            if(line == "Tower") {
                while (true) {
                    ++lineNum;

                    getline(saveFile, line);
                    if (line == "end") {
                        if (lineNum != 12)
                            throw invalid_argument("Invalid save file: Tower Section: Missing data");
                        break;
                    }

                    switch (lineNum) {
                        case 1:
                            id = stoi(line);
                            if (id < 0 || id > 5 || id == 2) // 2 is the id of the FireTower that needs different data and has its own section
                                throw invalid_argument("Invalid save file: Tower Section: Invalid ID: " + to_string(id) + " at tower spot " + to_string(towerSpot));
                            break;
                        case 2:
                            level = stoi(line);
                            break;
                        case 3:
                            damage = stod(line);
                            break;
                        case 4:
                            range = stoi(line);
                            break;
                        case 5:
                            cooldown = stoi(line);
                            break;
                        case 6:
                            pendingCooldown = stoi(line);
                            break;
                        case 7:
                            upgradeCost = stoi(line);
                            break;
                        case 8:
                            sellPrice = stoi(line);
                            break;
                        case 9:
                            towerTargeting = line;
                            break;
                        case 10:
                            positionX = stoi(line);
                            break;
                        case 11:
                            positionY = stoi(line);
                            break;
                        default:
                            throw invalid_argument("Invalid save file: Tower Section: Too many lines");
                    }
                }


                if(game.config.towerMaxLevel < level)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid level: " + to_string(level) + " at tower spot " + to_string(towerSpot));

                if(damage < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid damage: " + to_string(damage) + " at tower spot " + to_string(towerSpot));

                if(range < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid range: " + to_string(range) + " at tower spot " + to_string(towerSpot));

                if(cooldown < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid cooldown: " + to_string(cooldown) + " at tower spot " + to_string(towerSpot));

                if(pendingCooldown < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid pending cooldown: " + to_string(pendingCooldown) + " at tower spot " + to_string(towerSpot));

                if(upgradeCost < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid upgrade cost: " + to_string(upgradeCost) + " at tower spot " + to_string(towerSpot));

                if(sellPrice < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid sell price: " + to_string(sellPrice) + " at tower spot " + to_string(towerSpot));

                if(positionX < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid positionX: " + to_string(positionX) + " at tower spot " + to_string(towerSpot));

                if(positionY < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid positionY: " + to_string(positionY) + " at tower spot " + to_string(towerSpot));


                Coord position(positionX, positionY);

                if(game.towerSpots[towerSpot] != position)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid position: " + to_string(positionX) + ", " + to_string(positionY) + " at tower spot " + to_string(towerSpot));

                shared_ptr<Targeting> targetingPtr;

                if (towerTargeting == "Closest")
                    targetingPtr = make_shared<TargetingClosest>();
                else if (towerTargeting == "Strongest")
                    targetingPtr = make_shared<TargetingStrongest>();
                else if (towerTargeting == "Farthest")
                    targetingPtr = make_shared<TargetingFarthest>();
                else
                    throw invalid_argument("Invalid save file: Tower Section: Invalid targeting: " + towerTargeting + " at tower spot " + to_string(towerSpot));

                switch (id) {
                    case 1:
                        game.towers[towerSpot] = make_shared<Tower>(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, targetingPtr, position, game.config);
                        break;
                    case 3:
                        game.towers[towerSpot] = make_shared<IceTower>(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, targetingPtr, position, game.config);
                        break;
                    case 4:
                        game.towers[towerSpot] = make_shared<SniperTower>(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, targetingPtr, position, game.config);
                        break;
                    default:
                        throw invalid_argument("Invalid save file: Tower Section: Invalid ID" + to_string(id));
                }

            }


            else if(line == "FireTower"){
                while(true)
                {
                    ++lineNum;

                    getline(saveFile, line);
                    if(line == "end") {
                        if(lineNum < 12)
                            throw invalid_argument("Invalid save file: Tower Section: Missing data");
                        break;
                    }

                    switch(lineNum)
                    {
                        case 1:
                            id = stoi(line);
                            if( id != 2 )
                                throw invalid_argument("Invalid save file: Tower Section: Invalid ID" + to_string(id));
                            break;
                        case 2:
                            level = stoi(line);
                            break;
                        case 3:
                            damage = stod(line);
                            break;
                        case 4:
                            range = stoi(line);
                            break;
                        case 5:
                            cooldown = stoi(line);
                            break;
                        case 6:
                            pendingCooldown = stoi(line);
                            break;
                        case 7:
                            upgradeCost = stoi(line);
                            break;
                        case 8:
                            sellPrice = stoi(line);
                            break;
                        case 9:
                            towerTargeting = line;
                            break;
                        case 10:
                            positionX = stoi(line);
                            break;
                        case 11:
                            positionY = stoi(line);
                            break;
                        case 12:
                            intensity = stoi(line);
                            break;
                        default:
                            throw invalid_argument("Invalid save file: Tower Section: Too many lines");
                    }
                }

                if(game.config.towerMaxLevel < level)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid level: " + to_string(level) + " at tower spot " + to_string(towerSpot));

                if(damage < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid damage: " + to_string(damage) + " at tower spot " + to_string(towerSpot));

                if(range < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid range: " + to_string(range) + " at tower spot " + to_string(towerSpot));

                if(cooldown < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid cooldown: " + to_string(cooldown) + " at tower spot " + to_string(towerSpot));

                if(pendingCooldown < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid pending cooldown: " + to_string(pendingCooldown) + " at tower spot " + to_string(towerSpot));

                if(upgradeCost < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid upgrade cost: " + to_string(upgradeCost) + " at tower spot " + to_string(towerSpot));

                if(sellPrice < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid sell price: " + to_string(sellPrice) + " at tower spot " + to_string(towerSpot));

                if(positionX < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid positionX: " + to_string(positionX) + " at tower spot " + to_string(towerSpot));

                if(positionY < 0)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid positionY: " + to_string(positionY) + " at tower spot " + to_string(towerSpot));


                Coord position(positionX, positionY);

                if(game.towerSpots[towerSpot] != position)
                    throw invalid_argument("Invalid save file: Tower Section: Invalid position: " + to_string(positionX) + ", " + to_string(positionY) + " at tower spot " + to_string(towerSpot));

                shared_ptr<Targeting> targetingPtr;

                if (towerTargeting == "Closest")
                    targetingPtr = make_shared<TargetingClosest>();
                else if (towerTargeting == "Strongest")
                    targetingPtr = make_shared<TargetingStrongest>();
                else if (towerTargeting == "Farthest")
                    targetingPtr = make_shared<TargetingFarthest>();
                else
                    throw invalid_argument("Invalid save file: Tower Section: Invalid targeting: " + towerTargeting + " at tower spot " + to_string(towerSpot));



                game.towers[towerSpot] = make_shared<FireTower>(level, damage, range, cooldown, pendingCooldown, upgradeCost, sellPrice, targetingPtr, position, intensity, game.config);


            }
            else
                throw invalid_argument("Invalid save file: Tower Section: From Format, got " + line);

            game.map[game.towerSpots[towerSpot].x][game.towerSpots[towerSpot].y] = game.towers[towerSpot];

        }
        ++towerSpot;
        cout << "Tower loaded" << endl;
    }


    // Load enemies
    bool dragonAttackedBefore, saveToBuffer = false;
    int dragonInvisibilityCounter;
    int duration = 0;
    getline(saveFile, line);
    if(line != "---")
        throw invalid_argument("Invalid save file: Missing ---, got " + line);
    int type;
    while(true){
        getline(saveFile, line);
        if(line == "\n" || line.empty())
            break;
        else if(line == "---") {
            saveToBuffer = true;
            continue;
        }
        if(line != "Enemy")
            throw invalid_argument("Invalid save file: Enemy Section: From Format, got " + line);

        getline(saveFile, line);
        if(line == "Minion")
            type = 1;
        else if(line == "Orc")
            type = 2;
        else if(line == "Dragon")
            type = 3;
        else if(line == "Boss")
            type = 4;
        else
            throw invalid_argument("Invalid save file: Enemy Section: Invalid Type, got " + line);

        getline(saveFile, line);
        level = stoi(line);
        if(level < 0)
            throw invalid_argument("Invalid save file: Enemy Section: Invalid Level, got " + line);

        getline(saveFile, line);
        double healthD = stod(line);
        if(healthD < 0)
            throw invalid_argument("Invalid save file: Enemy Section: Invalid Health, got " + line);

        getline(saveFile, line);
        positionX = stoi(line);
        if(positionX < 0 || positionX > 60)
            throw invalid_argument("Invalid save file: Enemy Section: Invalid X Position, got " + line);

        getline(saveFile, line);
        positionY = stoi(line);
        if(positionY < 0 || positionY > 60)
            throw invalid_argument("Invalid save file: Enemy Section: Invalid Y Position, got " + line);

        // load Dragon specific variables
        if(type == 3){
            getline(saveFile, line);
            dragonAttackedBefore = stoi(line);
            getline(saveFile, line);
            dragonInvisibilityCounter = stoi(line);
        }

        // Spells
        vector<shared_ptr<Spell>> spells;
        while(getline(saveFile, line))
        {
            if (line == "Spell")
            {
                getline(saveFile, line);
                damage = stod(line);
                if(damage < 0)
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell Damage, got " + line);

                getline(saveFile, line);
                duration = stoi(line);
                if(duration < 0)
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell Duration, got " + line);

                getline(saveFile, line);
                if (line != "Spell-end")
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell-end, got " + line);

                spells.push_back(make_shared<Spell>(damage, duration));

            }

            else if (line == "FireSpell")
            {
                getline(saveFile, line);
                damage = stod(line);
                if(damage < 0)
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell Damage, got " + line);

                getline(saveFile, line);
                duration = stoi(line);
                if(duration < 0)
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell Duration, got " + line);

                getline(saveFile, line);
                intensity = stoi(line);
                if(intensity < 0)
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell Intensity, got " + line);

                getline(saveFile, line);
                if (line != "Spell-end")
                    throw invalid_argument("Invalid save file: Enemy Section: Invalid Spell-end, got " + line);

                spells.push_back(make_shared<FireSpell>(damage, duration, intensity));
            }
            else if(line == "end")
                break;

            else
                throw invalid_argument("Invalid save file: Enemy Section: From Format, got " + line);
        }


        Coord position(positionX, positionY);
        switch (type)
        {
            case 1:
                if(!saveToBuffer)
                    game.enemies.push_back(make_shared<Minion>(level, position, healthD, game.config));
                else
                    game.enemiesToSpawn.push_back(make_shared<Minion>(level, position, healthD, game.config));
                break;
            case 2:
                if(!saveToBuffer)
                    game.enemies.push_back(make_shared<Orc>(level, position, healthD, game.config));
                else
                    game.enemiesToSpawn.push_back(make_shared<Orc>(level, position, healthD, game.config));
                break;
            case 3:
                if(!saveToBuffer)
                    game.enemies.push_back(make_shared<Dragon>(level, position, healthD, dragonAttackedBefore, dragonInvisibilityCounter, game.config));
                else
                    game.enemiesToSpawn.push_back(make_shared<Dragon>(level, position, healthD, dragonAttackedBefore, dragonInvisibilityCounter, game.config));
                break;
            case 4:
                if(!saveToBuffer)
                    game.enemies.push_back(make_shared<Boss>(level, position, healthD, game.config));
                else
                    game.enemiesToSpawn.push_back(make_shared<Boss>(level, position, healthD, game.config));
                break;
        }
        if(!saveToBuffer) {
            game.enemies.back()->importPath(game.path);
            game.enemies.back()->syncPosition();
            game.enemies.back()->importSpells(spells);
            spells.clear();
            game.map[positionX][positionY] = game.enemies.back();
        }
        else{
            game.enemiesToSpawn.back()->importPath(game.path);
            game.enemiesToSpawn.back()->syncPosition();
            game.enemiesToSpawn.back()->importSpells(spells);
            spells.clear();
            game.map[positionX][positionY] = game.enemiesToSpawn.back();
        }

    }
}