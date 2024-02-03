#include "TargetingClosest.h"

TargetingClosest::TargetingClosest() {
    targetingName = "Closest";
}

shared_ptr<Enemy> TargetingClosest::getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const {

    shared_ptr<Enemy> tmp;
    double pivot;

    pivot = 1000000; // calculate minimal distance to any enemy
    for (auto & enemy : enemies) {
        double distance = position.distance(enemy->getPosition());
        if (distance < pivot && distance <= range) {
            pivot = distance;
            tmp = enemy;
        }
    }

    return tmp;
}


