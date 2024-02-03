#include <fstream>
#include <algorithm>
#include "GameStarter.h"

void GameStarter::prepareGame(GameState & game) {

    ifstream configFile (CONFIG_FILE);
    if (!configFile.is_open()) {
        throw runtime_error("Config file not found");
    }
    string mapName = ASSETS_PATH;
    mapName += loadConfig(configFile, game);

    // load UI
    ifstream file (UI_FILE);

    if (!file.is_open()) {
        throw runtime_error("UI file not found");
    }

    string textLine;
    int line = 0;

    while (getline(file, textLine)) {

        game.map.emplace_back();

        for (unsigned long col = 0; col < textLine.length(); col++) {
            switch (textLine[col]) {

                case ' ':
                    game.map[line].push_back(make_shared<Path>());
                    break;

                case '|': // ┃
                    game.map[line].push_back(make_shared<Wall>("┃"));
                    break;

                case '-': // ━
                    game.map[line].push_back(make_shared<Wall>("━"));
                    break;

                case '1': // ┏
                    game.map[line].push_back(make_shared<Wall>("┏"));
                    break;

                case '2': // ┓
                    game.map[line].push_back(make_shared<Wall>("┓"));
                    break;

                case '3': // ┛
                    game.map[line].push_back(make_shared<Wall>("┛"));
                    break;

                case '4': // ┗
                    game.map[line].push_back(make_shared<Wall>("┗"));
                    break;

                case '5': // ┳
                    game.map[line].push_back(make_shared<Wall>("┳"));
                    break;

                case '6': // ┫
                    game.map[line].push_back(make_shared<Wall>("┫"));
                    break;

                case '7': // ┻
                    game.map[line].push_back(make_shared<Wall>("┻"));
                    break;

                case '8': // ┣
                    game.map[line].push_back(make_shared<Wall>("┣"));
                    break;

                case '+': // ╋
                    game.map[line].push_back(make_shared<Wall>("╋"));
                    break;

                case '9': // ░
                    game.map[line].push_back(make_shared<FreeTowerSpot>());
                    game.towerSpots.emplace_back(line, col);
                    game.towers.emplace_back();
                    break;

                case '!':
                    game.spawnPoint.x = line;
                    game.spawnPoint.y = col;
                    game.map[line].push_back(make_shared<Path>());
                    break;

                case '?':
                    game.endPoint.x = line;
                    game.endPoint.y = col;
                    game.map[line].push_back(make_shared<Character>("Ѫ"));
                    break;

                default:
                    if((textLine[col] >= 'a' && textLine[col] <= 'z') || (textLine[col] >= 'A' && textLine[col] <= 'Z') || textLine[col] == ':' || textLine[col] == ')')
                        game.map[line].push_back(make_shared<Character>(textLine[col]));
                    else
                        throw runtime_error("Invalid character in UI.txt");
                    break;
            }
        }

        line++;
    }

    // load map
    ifstream mapFile (mapName);

    if (!mapFile.is_open()) {
        throw runtime_error("Map file not found!");
    }

    line = 1; // offset for UI
    int colOffset = 1; // offset for UI
    bool isSpawnPoint = false;
    bool isEndPoint = false;

    while (getline(mapFile, textLine)) {

        for (unsigned long col = 0; col < textLine.length(); col++) {
            if(col > 58) // 58 is max width of map
                throw runtime_error("Map is too big!");

            switch (textLine[col]) {

                case ' ':
                    game.map[line][col + colOffset] = (make_shared<Path>());
                    break;

                case '|': // ┃
                    game.map[line][col + colOffset] = (make_shared<Wall>("┃"));
                    break;

                case '-': // ━
                    game.map[line][col + colOffset] = (make_shared<Wall>("━"));
                    break;

                case '1': // ┏
                    game.map[line][col + colOffset] = (make_shared<Wall>("┏"));
                    break;

                case '2': // ┓
                    game.map[line][col + colOffset] = (make_shared<Wall>("┓"));
                    break;

                case '3': // ┛
                    game.map[line][col + colOffset] = (make_shared<Wall>("┛"));
                    break;

                case '4': // ┗
                    game.map[line][col + colOffset] = (make_shared<Wall>("┗"));
                    break;

                case '5': // ┳
                    game.map[line][col + colOffset] = (make_shared<Wall>("┳"));
                    break;

                case '6': // ┫
                    game.map[line][col + colOffset] = (make_shared<Wall>("┫"));
                    break;

                case '7': // ┻
                    game.map[line][col + colOffset] = (make_shared<Wall>("┻"));
                    break;

                case '8': // ┣
                    game.map[line][col + colOffset] = (make_shared<Wall>("┣"));
                    break;

                case '+': // ╋
                    game.map[line][col + colOffset] = (make_shared<Wall>("╋"));
                    break;

                case '9': // ░
                    game.map[line][col + colOffset] = (make_shared<FreeTowerSpot>());
                    game.towerSpots.emplace_back(line, col + colOffset);
                    game.towers.emplace_back();
                    break;

                case '!':
                    if(isSpawnPoint)
                        throw runtime_error("Multiple spawn points!");
                    isSpawnPoint = true;
                    game.spawnPoint.x = line;
                    game.spawnPoint.y = col + colOffset;
                    game.map[line][col + colOffset] = (make_shared<Path>());
                    break;

                case '?':
                    if(isEndPoint)
                        throw runtime_error("Multiple endpoints!");
                    isEndPoint = true;
                    game.endPoint.x = line;
                    game.endPoint.y = col + colOffset;
                    game.map[line][col + colOffset] = (make_shared<Character>("Ѫ"));
                    break;

                default:
                    throw runtime_error("Invalid character in UI.txt");
            }
        }

        line++;
        if(line > 18) // 18 is max height of map
            throw runtime_error("Map is too big!");
    }

    if(!isSpawnPoint)
        throw runtime_error("No spawn point!");

    if(!isEndPoint)
        throw runtime_error("No endpoint!");

    generateBFSMap(game);

    file.close();
    mapFile.close();
    configFile.close();

}

string GameStarter::loadConfig(ifstream & configFile, GameState & game) {
    string line;
    string mapName;

    // get map name
    mapName = getAndParse(configFile, 4, true);

    // Start Money
    game.money = stoi(getAndParse(configFile, 15));

    // Start Lives
    game.health = stoi(getAndParse(configFile, 16));

    // get Tower parameters
    getline(configFile, line);
    if(line[0] != '-')
        throw runtime_error(R"(Invalid config file! Missing "-" at the start of line 4, got ")" + line + "\" instead");

    getline(configFile, line);
    if(line != "Tower")
        throw runtime_error(R"(Invalid config file! Missing "Tower" on line 5, got ")" + line + "\" instead");

    // Tower Cost
    game.config.towerCost = stoi(getAndParse(configFile, 15));

    // Tower Damage
    game.config.towerDamage = stod(getAndParse(configFile, 21));

    // Tower Range
    game.config.towerRange = stoi(getAndParse(configFile, 12));

    // Tower Cooldown
    game.config.towerCooldown = stoi(getAndParse(configFile, 15));

    // Tower Upgrade Cost
    game.config.towerUpgradeCost = stoi(getAndParse(configFile, 19));

    // Tower Sell Price
    game.config.towerSellPrice = stoi(getAndParse(configFile, 17));

    // Tower Max Level
    game.config.towerMaxLevel = stoi(getAndParse(configFile, 16));

    // Tower Upgrade Damage Scalar
    game.config.towerUpgradeDamageScalar = stod(getAndParse(configFile, 32));

    // Tower Upgrade Cost Scalar
    game.config.towerUpgradeCostScalar = stoi(getAndParse(configFile, 29));

    // Tower Upgrade Sell Price Scalar
    game.config.towerUpgradeSellPriceScalar = stod(getAndParse(configFile, 36));

    // Text spacing
    getline(configFile, line);
    if (line != "Tower")
        throw runtime_error(R"(Invalid config file! Missing "Tower" on line 16, got ")" + line + "\" instead");
    getline(configFile, line);
    if(line[0] != '-')
        throw runtime_error(R"(Invalid config file! Missing "-" at the start of line 17, got ")" + line + "\" instead");
    getline(configFile, line);
    if (line != "FireTower")
        throw runtime_error(R"(Invalid config file! Missing "FireTower" on line 18, got ")" + line + "\" instead");

    // FireTower Intensity
    game.config.towerFireIntensity = stoi(getAndParse(configFile, 21));

    // FireTower Intensity Scalar
    game.config.towerFireIntensityScalar = stoi(getAndParse(configFile, 28));

    // Text spacing
    getline(configFile, line);
    if (line != "FireTower")
        throw runtime_error(R"(Invalid config file! Missing "FireTower" on line 21, got ")" + line + "\" instead");
    getline(configFile, line);
    if(line[0] != '-')
        throw runtime_error(R"(Invalid config file! Missing "-" at the start of line 22, got ")" + line + "\" instead");
    getline(configFile, line);
    if (line != "SpecializingTower")
        throw runtime_error(R"(Invalid config file! Missing "SpecializingTower" on line 23, got ")" + line + "\" instead");

    // Specialization FireTower Damage Scalar
    game.config.towerFireDamageScalar = stod(getAndParse(configFile, 34));

    // Specialization FireTower Range Scalar
    game.config.towerFireRangeScalar = stoi(getAndParse(configFile, 30));

    // Specialization FireTower Cooldown Scalar
    game.config.towerFireCooldownScalar = stoi(getAndParse(configFile, 33));

    // Specialization IceTower Damage Scalar
    game.config.towerIceDamageScalar = stod(getAndParse(configFile, 33));

    // Specialization IceTower Range Scalar
    game.config.towerIceRangeScalar = stoi(getAndParse(configFile, 29));

    // Specialization IceTower Cooldown Scalar
    game.config.towerIceCooldownScalar = stoi(getAndParse(configFile, 32));

    // Specialization SniperTower Damage Scalar
    game.config.towerSniperDamageScalar = stod(getAndParse(configFile, 36));

    // Specialization SniperTower Range Scalar
    game.config.towerSniperRangeScalar = stoi(getAndParse(configFile, 32));

    // Specialization SniperTower Cooldown Scalar
    game.config.towerSniperCooldownScalar = stoi(getAndParse(configFile, 35));

    // Text spacing
    getline(configFile, line);
    if (line != "SpecializingTower")
        throw runtime_error(R"(Invalid config file! Missing "SpecializingTower" on line 33, got ")" + line + "\" instead");
    getline(configFile, line);
    if(line[0] != '-')
        throw runtime_error(R"(Invalid config file! Missing "-" at the start of line 34, got ")" + line + "\" instead");
    getline(configFile, line);
    if (line != "Enemy")
        throw runtime_error(R"(Invalid config file! Missing "Enemy" on line 35, got ")" + line + "\" instead");

    // Enemy Goblin Health Scalar
    game.config.enemyMinionHealthScalar = stod(getAndParse(configFile, 31));

    // Enemy Goblin Speed
    game.config.enemyMinionSpeed = stoi(getAndParse(configFile, 20));

    // Enemy Goblin Reward Scalar
    game.config.enemyMinionRewardScalar = stoi(getAndParse(configFile, 28));

    // Enemy Orc Health Scalar
    game.config.enemyOrcHealthScalar = stod(getAndParse(configFile, 28));

    // Enemy Orc Speed
    game.config.enemyOrcSpeed = stoi(getAndParse(configFile, 17));

    // Enemy Orc Reward Scalar
    game.config.enemyOrcRewardScalar = stoi(getAndParse(configFile, 25));

    // Enemy Orc Armor
    game.config.enemyOrcArmor = stod(getAndParse(configFile, 38));

    // Enemy Dragon Health Scalar
    game.config.enemyDragonHealthScalar = stod(getAndParse(configFile, 31));

    // Enemy Dragon Speed
    game.config.enemyDragonSpeed = stoi(getAndParse(configFile, 20));

    // Enemy Dragon Reward Scalar
    game.config.enemyDragonRewardScalar = stoi(getAndParse(configFile, 28));

    // Enemy Dragon Invisibility Duration
    game.config.enemyDragonInvisibilityDuration = stoi(getAndParse(configFile, 36));

    // Enemy Boss Health Scalar
    game.config.enemyBossHealthScalar = stod(getAndParse(configFile, 29));

    // Enemy Boss Speed
    game.config.enemyBossSpeed = stoi(getAndParse(configFile, 18));

    // Enemy Boss Reward Scalar
    game.config.enemyBossRewardScalar = stoi(getAndParse(configFile, 26));

    // Enemy Boss Regeneration Scalar
    game.config.enemyBossRegenerationScalar = stoi(getAndParse(configFile, 39));

    //Text spacing
    getline(configFile, line);
    if (line != "Enemy")
        throw runtime_error(R"(Invalid config file! Missing "Enemy" on line 51, got ")" + line + "\" instead");
    getline(configFile, line);
    if(line[0] != '-')
        throw runtime_error(R"(Invalid config file! Missing "-" at the start of line 52, got ")" + line + "\" instead");

    // Check invalid values
    if(game.config.towerCost < 0 ||
       game.config.towerDamage < 0 ||
       game.config.towerRange < 0 ||
       game.config.towerCooldown < 0 ||
       game.config.towerUpgradeCost < 0 ||
       game.config.towerSellPrice < 0 ||
       game.config.towerUpgradeCostScalar < 0 ||
       game.config.towerUpgradeSellPriceScalar < 0 ||
       game.config.towerUpgradeDamageScalar < 0 ||
       game.config.towerMaxLevel < 0 ||
       game.config.towerFireIntensity < 0 ||
       game.config.towerFireIntensityScalar < 0 ||
       game.config.towerFireDamageScalar < 0 ||
       game.config.towerIceDamageScalar < 0 ||
       game.config.towerSniperDamageScalar < 0 ||
       game.config.enemyMinionHealthScalar < 1 ||
       game.config.enemyMinionSpeed < 1 ||
       game.config.enemyMinionRewardScalar < 0 ||
       game.config.enemyOrcHealthScalar < 1 ||
       game.config.enemyOrcSpeed < 1 ||
       game.config.enemyOrcRewardScalar < 0 ||
       game.config.enemyOrcArmor < 0 || game.config.enemyOrcArmor > 1 ||
       game.config.enemyDragonHealthScalar < 1 ||
       game.config.enemyDragonSpeed < 1 ||
       game.config.enemyDragonRewardScalar < 0 ||
       game.config.enemyDragonInvisibilityDuration < 0 ||
       game.config.enemyBossHealthScalar < 1 ||
       game.config.enemyBossSpeed < 1 ||
       game.config.enemyBossRewardScalar < 0 ||
       game.config.enemyBossRegenerationScalar < 0 ||
       game.health < 0 ||
       game.money < 0)
        throw runtime_error("Invalid config file! Negative values, values below 1 in some scalars and values below 0 and above 1 in Orc Armor are not allowed!");


    /*// debug - print config
    cout << "Tower Cost: " << game.config.towerCost << endl;
    cout << "Tower Damage: " << game.config.towerDamage << endl;
    cout << "Tower Range: " << game.config.towerRange << endl;
    cout << "Tower Cooldown: " << game.config.towerCooldown << endl;
    cout << "Tower Upgrade Cost: " << game.config.towerUpgradeCost << endl;
    cout << "Tower Sell Price: " << game.config.towerSellPrice << endl;
    cout << "Tower Upgrade Cost Scalar: " << game.config.towerUpgradeCostScalar << endl;
    cout << "Tower Upgrade Sell Price Scalar: " << game.config.towerUpgradeSellPriceScalar << endl;
    cout << "Tower Upgrade Damage Scalar: " << game.config.towerUpgradeDamageScalar << endl;
    cout << "Tower Max Level: " << game.config.towerMaxLevel << endl;
    cout << "Tower Fire Intensity: " << game.config.towerFireIntensity << endl;
    cout << "Tower Fire Intensity Scalar: " << game.config.towerFireIntensityScalar << endl;
    cout << "Tower Fire Damage Scalar: " << game.config.towerFireDamageScalar << endl;
    cout << "Tower Ice Damage Scalar: " << game.config.towerIceDamageScalar << endl;
    cout << "Tower Sniper Damage Scalar: " << game.config.towerSniperDamageScalar << endl;
    cout << "Enemy Minion Health Scalar: " << game.config.enemyMinionHealthScalar << endl;
    cout << "Enemy Minion Speed: " << game.config.enemyMinionSpeed << endl;
    cout << "Enemy Minion Reward Scalar: " << game.config.enemyMinionRewardScalar << endl;
    cout << "Enemy Orc Health Scalar: " << game.config.enemyOrcHealthScalar << endl;
    cout << "Enemy Orc Speed: " << game.config.enemyOrcSpeed << endl;
    cout << "Enemy Orc Reward Scalar: " << game.config.enemyOrcRewardScalar << endl;
    cout << "Enemy Orc Armor: " << game.config.enemyOrcArmor << endl;
    cout << "Enemy Dragon Health Scalar: " << game.config.enemyDragonHealthScalar << endl;
    cout << "Enemy Dragon Speed: " << game.config.enemyDragonSpeed << endl;
    cout << "Enemy Dragon Reward Scalar: " << game.config.enemyDragonRewardScalar << endl;
    cout << "Enemy Dragon Invisibility Duration: " << game.config.enemyDragonInvisibilityDuration << endl;
    cout << "Enemy Boss Health Scalar: " << game.config.enemyBossHealthScalar << endl;
    cout << "Enemy Boss Speed: " << game.config.enemyBossSpeed << endl;
    cout << "Enemy Boss Reward Scalar: " << game.config.enemyBossRewardScalar << endl;
    cout << "Enemy Boss Regeneration Scalar: " << game.config.enemyBossRegenerationScalar << endl;
    cin.get();*/



    return mapName;
}

void GameStarter::generateBFSMap(GameState & game) {
    BFS bfs(game.map);
    game.path = bfs(game.spawnPoint, game.endPoint);
}

string GameStarter::getAndParse(ifstream & stream, int pos, bool keepChars) {

    string str;
    getline(stream, str);
    str = str.substr(pos);
    str.erase(remove_if(str.begin(), str.end(), [keepChars](int i){
                                                                                    if( ::isdigit(i) || i == '.' || i == '+' || i == '-' || ( keepChars && (isalnum(i)) ) )
                                                                                        return false;
                                                                                    else
                                                                                        return true;
                                                                                                    } ), str.end());

    return str;
}
