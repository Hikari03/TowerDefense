#include "TargetingStrongest.h"

TargetingStrongest::TargetingStrongest() {
    targetingName = "Strongest";
}

shared_ptr<Enemy> TargetingStrongest::getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const {

    shared_ptr<Enemy> tmp;
    double pivot;

    pivot = 0;
    for (auto & enemy : enemies) {
        double distance = position.distance(enemy->getPosition());
        if (enemy->getHealth() > pivot && distance <= range) {
            pivot = enemy->getHealth();
            tmp = enemy;
        }
    }

    return tmp;
}