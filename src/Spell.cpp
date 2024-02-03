#include "Spell.h"

Spell::Spell(double damage, int duration) : damage(damage), duration(duration) {}

Spell::Spell(const Spell &other) : damage(other.damage), duration(other.duration) {
    Type = other.Type;
}


// ##### Spell Methods #################################################################################################

int Spell::getDuration() const {
    return duration;
}

double Spell::getDamage() {
    return damage;
}

Spell::SpellType Spell::type() const {
    return Type;
}

string Spell::Export() const {
    string s;
    s += "Spell\n";
    s += to_string(damage) + '\n';
    s += to_string(duration) + '\n';
    s += "Spell-end\n";
    return s;
}

