#ifndef TOWER_DEFENCE_TARGETING_H
#define TOWER_DEFENCE_TARGETING_H

#include "Enemy.h"

/**
 * @brief Base class for targeting algorithms
 */
class Targeting {
public:
    Targeting() = default;

    virtual shared_ptr<Enemy> getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const = 0;

    const string & targeting() const;

protected:
    string targetingName = "Err";

};


#endif //TOWER_DEFENCE_TARGETING_H
