#ifndef TOWER_DEFENCE_TARGETINGFARTHEST_H
#define TOWER_DEFENCE_TARGETINGFARTHEST_H


#include "Targeting.h"

/**
 * @brief Targets the farthest enemy
 */
class TargetingFarthest : public Targeting {
public:
    TargetingFarthest();

    shared_ptr<Enemy> getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const override;

};


#endif //TOWER_DEFENCE_TARGETINGFARTHEST_H
