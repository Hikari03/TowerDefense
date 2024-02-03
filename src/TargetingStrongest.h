#ifndef TOWER_DEFENCE_TARGETINGSTRONGEST_H
#define TOWER_DEFENCE_TARGETINGSTRONGEST_H


#include "Targeting.h"

/**
 * @brief Targets the strongest enemy
 */
class TargetingStrongest : public Targeting {
public:
    TargetingStrongest();

    shared_ptr<Enemy> getTarget(vector<shared_ptr<Enemy>> & enemies, const Coord & position, int range) const override;

};


#endif //TOWER_DEFENCE_TARGETINGSTRONGEST_H
