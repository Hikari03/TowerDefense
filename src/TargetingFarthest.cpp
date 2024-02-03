#include "TargetingFarthest.h"

TargetingFarthest::TargetingFarthest() {
    targetingName = "Farthest";
}

shared_ptr<Enemy> TargetingFarthest::getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const {

    shared_ptr<Enemy> tmp;
    double pivot;

    pivot = 0; // calculate maximal distance to any enemy
    for (auto & enemy : enemies) {
        double distance = position.distance(enemy->getPosition());
        if (distance > pivot && distance <= range) {
            pivot = distance;
            tmp = enemy;
        }
    }

    return tmp;
}