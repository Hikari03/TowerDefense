#ifndef TOWER_DEFENCE_BFS_H
#define TOWER_DEFENCE_BFS_H

#include <iostream>
#include <vector>
#include <queue>
#include "Coord.h"
#include "Tile.h"


using namespace std;

/**
 * @brief Implements path finding
 * @details This class is used to find shortest path between two coordinates
 */
class BFS {
public:
    BFS(const vector<vector<shared_ptr<Tile>>> & map);
    ~BFS() = default;

    /**
     * @brief Finds shortest path from start to end
     * @param start
     * @param end
     * @return
     */
    vector<Coord> operator () (const Coord & start, const Coord & end );

    /**
     * @brief Prints map with path - used for debugging
     * @param path
     */
    void printMapWithPath(const vector<Coord> & path);


private:
    vector<vector<shared_ptr<Tile>>> map;
    vector<vector<bool>> visited;

    /**
     * @brief Checks if coord is valid for path
     * @param coord
     * @return
     */
    bool isValid(const Coord & coord);

};


#endif //TOWER_DEFENCE_BFS_H
