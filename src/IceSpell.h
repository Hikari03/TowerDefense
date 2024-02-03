#ifndef TOWER_DEFENCE_ICESPELL_H
#define TOWER_DEFENCE_ICESPELL_H

#include "Spell.h"

/**
 * @brief Spell that stuns enemy
 */
class IceSpell : public Spell {
public:
    explicit IceSpell(int duration);
    IceSpell(const IceSpell & other);
};


#endif //TOWER_DEFENCE_ICESPELL_H
