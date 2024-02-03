#include "GameUpdater.h"
#include <iostream>
#include <unistd.h>

GameUpdater::GameUpdater(GameState & game) : game(game) {}

void GameUpdater::sendWave() {

    bool towersEmpty;
    for (const auto & tower : game.towers) {
        if(tower != nullptr) {
            towersEmpty = false;
            break;
        }
        else {
            towersEmpty = true;
        }
    }

    if(game.wave == 0 && towersEmpty) {
        cout << "\n" RED "You have to build a tower before you can send a wave" RESET << endl;
        sleep(1);
        return;
    }

    if(game.wave > 0 && game.wave < 10 && !game.enemies.empty()) {
        cout << "\n" RED "You have to wait for the wave to finish before you can send a new one" RESET << endl;
        sleep(1);
        return;
    }

    game.wave++;

    pair<int, int> waveInfo = evaluateDifficulty();

    for(int i = 0; i < (waveInfo.second / 3)+1; i++) {
        game.enemiesToSpawn.push_back(make_shared<Minion>(waveInfo.first, game.spawnPoint, game.config));
        game.enemiesToSpawn.push_back(make_shared<Orc>(waveInfo.first, game.spawnPoint, game.config));
        game.enemiesToSpawn.push_back(make_shared<Dragon>(waveInfo.first, game.spawnPoint, game.config));
    }

    if(game.wave % 2 == 0)
        for(int i = 0; i < game.wave/2; i++)
            game.enemiesToSpawn.push_back(make_shared<Boss>(waveInfo.first, game.spawnPoint, game.config));

    game.enemiesLeft = game.enemiesToSpawn.size();
    spawnEnemy(game.enemiesToSpawn.front());
    game.enemiesToSpawn.erase(game.enemiesToSpawn.begin());
    game.enemiesToSpawn.shrink_to_fit();


    cout << "\n" GREEN "Wave " << game.wave << " sent" RESET << endl;
    sleep(1);
}

pair<int, int> GameUpdater::evaluateDifficulty() const {
    double totalTowerDamage = 0;

    for (const auto & tower : game.towers) {
        if(tower != nullptr) {
            totalTowerDamage += tower->getDamage();
        }
    }
    //calculate how many enemies we send
    int enemiesToSend = static_cast<int>(game.wave * 0.5 + 1 + (totalTowerDamage / 100));
    return {game.wave/2 == 0 ? 1 : game.wave/2, enemiesToSend};
}

void GameUpdater::update() {

    // Move all enemies
    for(auto enemy = game.enemies.begin(); enemy != game.enemies.end(); ++enemy ) {

        game.map[(*enemy)->getPosition().x][(*enemy)->getPosition().y] = make_shared<Path>();
        (*enemy)->move();

        if((*enemy)->getPosition().x == game.endPoint.x && (*enemy)->getPosition().y == game.endPoint.y) {
            --game.health;
            game.enemies.erase(enemy);
            --enemy;
            game.enemiesLeft--;
        }


        if(game.health == 0)
            game.gameOver = true;
    }

    for(const auto & enemy : game.enemies)
        game.map[enemy->getPosition().x][enemy->getPosition().y] = enemy;

    // Check if any enemy is in range of any tower
    for(auto & tower : game.towers) {
        if(tower == nullptr)
            continue;

        tower->attack(game.enemies);
    }

    // check if any enemy is dead
    for(auto enemy = game.enemies.begin(); enemy != game.enemies.end(); ++enemy) {
        if((*enemy)->isDead())
        {
            game.enemiesKilled++;
            game.enemiesLeft--;
            if((game.money + (*enemy)->getReward()) < 0) {
            cout << "\n" RED "You have too much money, so you will not get any >:)" RESET << endl;
            sleep(1);
            }
            else
                game.money += (*enemy)->getReward();

            game.score += (*enemy)->getReward() * game.wave;
            game.map[(*enemy)->getPosition().x][(*enemy)->getPosition().y] = make_shared<Path>();

            game.enemies.erase(enemy);
            --enemy;
        }

    }

    if(game.enemies.size() < 12 && !game.enemiesToSpawn.empty())
    {
        if(game.enemiesToSpawn.front() != nullptr){
            spawnEnemy(game.enemiesToSpawn.front());
            game.enemiesToSpawn.erase(game.enemiesToSpawn.begin());
            game.enemiesToSpawn.shrink_to_fit();
        }
    }
}

void GameUpdater::spawnEnemy(int level, int type) {
    switch (type){
        case 1:
            game.enemies.emplace_back(make_shared<Minion>(level, game.spawnPoint, game.config));
            break;
        case 2:
            game.enemies.emplace_back(make_shared<Orc>(level, game.spawnPoint, game.config));
            break;
        case 3:
            game.enemies.emplace_back(make_shared<Dragon>(level, game.spawnPoint, game.config));
            break;
        case 4:
            game.enemies.emplace_back(make_shared<Boss>(level, game.spawnPoint, game.config));
            break;

        default:
            throw invalid_argument("Invalid enemy type: " + to_string(type));
    }
    game.enemies.back()->importPath(game.path);
    game.map[game.spawnPoint.x][game.spawnPoint.y] = game.enemies.back();

}

void GameUpdater::spawnEnemy(shared_ptr<Enemy> & enemy) {
    enemy->importPath(game.path);
    game.enemies.push_back(enemy);
    game.map[game.spawnPoint.x][game.spawnPoint.y] = game.enemies.back();
}

