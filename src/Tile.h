#ifndef TOWER_DEFENCE_TILE_H
#define TOWER_DEFENCE_TILE_H
#include <string>
#include <memory>

using namespace std;

/**
 * @brief Used for rendering
 * @details Tile class is a base class for all tiles in the game.\n
 *          It is used for rendering the game.
 */
class Tile {
public:
    virtual void printChar() const;
    Tile() = default;
    ~Tile() = default;
    Tile(const Tile & other) = default;

    void setChar(char c);

    void setChar(const string & c);

    string getChar() const;


    enum class Type {
        PATH,
        WALL,
        FREE_TOWER_SPOT,
        ENEMY,
        TOWER,
        ERR
    };

    Type type() const;

protected:
    string ch = "err";
    Type tileType = Type::ERR;

};

#endif //TOWER_DEFENCE_TILE_H
