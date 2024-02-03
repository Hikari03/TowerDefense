#ifndef TOWER_DEFENCE_TARGETINGCLOSEST_H
#define TOWER_DEFENCE_TARGETINGCLOSEST_H


#include "Targeting.h"

/**
 * @brief Targets the closest enemy
 */
class TargetingClosest : public Targeting {
public:
    TargetingClosest();

    shared_ptr<Enemy> getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const override;



};


#endif //TOWER_DEFENCE_TARGETINGCLOSEST_H
