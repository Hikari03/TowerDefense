#include "FireSpell.h"

FireSpell::FireSpell(double damage, int duration, int intensity) : Spell(damage, duration), intensity(intensity) {
    Type = SpellType::FIRE;
}

FireSpell::FireSpell(const FireSpell &other) : Spell(other), intensity(other.intensity) {
    Type = SpellType::FIRE;
}

double FireSpell::getDamage() {
    return damage * ( static_cast<double>(intensity) / 5 );
}

string FireSpell::Export() const {
    string s;
    s += "FireSpell\n";
    s += to_string(damage) + '\n';
    s += to_string(duration) + '\n';
    s += to_string(intensity) + '\n';
    s += "Spell-end\n";
    return s;
}