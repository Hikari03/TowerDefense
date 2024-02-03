#ifndef TOWER_DEFENCE_SPELL_H
#define TOWER_DEFENCE_SPELL_H

#include <string>

using namespace std;

/**
 * @brief Base class for all spells
 */
class Spell {
public:
    Spell() = default;
    Spell(double damage, int duration);
    Spell(const Spell & other);
    ~Spell() = default;

    void operator--(){
        duration--;
    }

    virtual double getDamage();

    int getDuration() const;

    enum class SpellType{
        ERR,
        FIRE,
        ICE
    };

    SpellType type() const;

    /**
     * @brief Exports the spell to a string
     * @return string
     */
    virtual string Export() const;

protected:
    double damage = -1;
    int duration;
    SpellType Type = SpellType::ERR;
};






#endif //TOWER_DEFENCE_SPELL_H
