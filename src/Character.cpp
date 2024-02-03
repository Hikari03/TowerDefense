#include "Character.h"

Character::Character(char c) {
    ch = c;
    tileType = Type::PATH;
}

Character::Character(const string & c) {
    ch = c;
    tileType = Type::PATH;
}

void Character::printChar() const {
    cout << "\033[1;32m" << ch << "\033[0m";
}