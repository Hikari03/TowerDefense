#include <algorithm>
#include "BFS.h"

BFS::BFS(const vector<vector<shared_ptr<Tile>>> & map) : map(map) {}




vector<Coord> BFS::operator() (const Coord &start, const Coord &end) {

    vector<pair<Coord, Coord>> path;
    visited.clear();

    queue<Coord> toExplore;
    toExplore.push(start);
    visited.resize(map.size(), vector<bool>(map[0].size(), false));
    visited[start.x][start.y] = true;

    while (!toExplore.empty()) {
        Coord current = toExplore.front();
        toExplore.pop();

        if(!isValid(current)) {
            continue;
        }

        if (current == end) {
            break;
        }

        vector<Coord> neighbours;

        neighbours.emplace_back(current.x + 1, current.y);
        neighbours.emplace_back(current.x - 1, current.y);
        neighbours.emplace_back(current.x, current.y + 1);
        neighbours.emplace_back(current.x, current.y - 1);

        for (const Coord & neighbour : neighbours) {
            if (isValid(neighbour) && !visited[neighbour.x][neighbour.y]) {
                toExplore.push(neighbour);
                visited[neighbour.x][neighbour.y] = true;
                path.emplace_back(current, neighbour);
            }
        }

    }

    vector<Coord> finalPath;
    Coord current = end;
    finalPath.push_back(current);
    while (current != start) {
        for (const pair<Coord, Coord> & p : path) {
            if (p.second == current) {
                current = p.first;
                finalPath.push_back(current);
                break;
            }
        }
    }

    reverse(finalPath.begin(), finalPath.end());


    return finalPath;

}


void BFS::printMapWithPath(const vector<Coord> & path) {
    cout << "Map:" << endl;
    for (unsigned long int i = 0; i < map.size(); i++) {
        cout << "\t";
        for (unsigned long int j = 0; j < map[i].size(); j++) {
            if (map[i][j]->type() == Tile::Type::PATH) {
                bool isPath = false;
                for (const Coord & coord : path) {
                    if (coord == Coord(i, j)) {
                        isPath = true;
                        break;
                    }
                }
                if (isPath) {
                    cout << "P";
                } else {
                    cout << " ";
                }
            } else {
                cout << "X";
            }
        }
        cout << endl;
    }
}

bool BFS::isValid(const Coord &coord) {
    return coord.x >= 0 && static_cast<unsigned long>(coord.x) < map.size() && coord.y >= 0 && static_cast<unsigned long>(coord.y) < map[0].size() && map[coord.x][coord.y]->type() == Tile::Type::PATH;
}

