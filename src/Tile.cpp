#include <iostream>
#include "Tile.h"

using namespace std;

void Tile::printChar() const {
    cout << ch;
}

void Tile::setChar(char c) {
    ch = c;
}

void Tile::setChar(const string & c) {
    ch = c;
}

string Tile::getChar() const {
    return ch;
}

Tile::Type Tile::type() const {
    return tileType;
}

