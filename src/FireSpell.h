#ifndef TOWER_DEFENCE_FIRESPELL_H
#define TOWER_DEFENCE_FIRESPELL_H


#include "Spell.h"

/**
 * @brief Spell that deals damage over time
 */
class FireSpell : public Spell {
public:
    explicit FireSpell(double damage, int duration, int intensity);
    FireSpell(const FireSpell & other);

    double getDamage() override;

    string Export() const override;



private:
    int intensity;

};


#endif //TOWER_DEFENCE_FIRESPELL_H
