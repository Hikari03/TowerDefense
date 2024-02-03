#include "IceSpell.h"

IceSpell::IceSpell(int duration) : Spell(0, duration){
    Type = SpellType::ICE;
}

IceSpell::IceSpell(const IceSpell &other) : Spell(other) {
    Type = SpellType::ICE;
}