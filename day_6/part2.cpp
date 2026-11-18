#include "part2.h"

struct Tile {
    bool isObstacle = false;
    bool isVisited = false;
};

struct Pos {
    int yPos = 0;
    int xPos = 0;

    bool operator==(const Pos& other) const {
        return yPos == other.yPos && xPos == other.xPos;
    }

    bool operator!=(const Pos& other) const {
        return !(*this == other);
    }
};

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input-file>\n";
        return EXIT_FAILURE;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Could not open " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    vector<vector<Tile>> map;
    vector<Tile> row;
    int pos[2];

    int x = 0;
    int y = 0;
    char tile;
    while (input.get(tile)) {
        if (tile == '\n') {
            map.push_back(row);
            row.clear();
            y++;
            x = 0;
        } else if (tile == '#') {
            row.push_back({true});
            x++;
        } else if (tile == '^') {
            pos[1] = x;
            pos[0] = y;
            row.push_back({false});
            x++;
        } else {
            row.push_back({false});
            x++;
        }
    }
    map.push_back(row);

    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dirNum = 0;

    x = pos[1];
    y = pos[0];

    while (y < map.size() && x < map[y].size() && y >= 0 && x >= 0) {
        int newX = x + dirs[dirNum][1];
        int newY = y + dirs[dirNum][0];
        if (newY < map.size() && newX < map[y].size() && newY >= 0 && newX >= 0) {
            while (map[newY][newX].isObstacle) {
                dirNum = (dirNum+1) % 4;
                newX = x + dirs[dirNum][1];
                newY = y + dirs[dirNum][0];
            }
            x = newX;
            y = newY;
            if (!map[y][x].isVisited) {
                map[y][x].isVisited = true;
            }
        } else {
            break;
        }
    }

    int numSuccessfulPositions = 0;

    int width = static_cast<int>(map[0].size());
    int trial = 1;

    for (int obstacleY = 0; obstacleY < map.size(); obstacleY++) {
        for (int obstacleX = 0; obstacleX < map[obstacleY].size(); obstacleX++) {
            // dont put an obstacle on another obstacle
            if (!map[obstacleY][obstacleX].isVisited) continue;

            map[obstacleY][obstacleX].isObstacle = true;
            // check if obstacle here traps the guard in a loop
            int dirNum = 0;

            x = pos[1];
            y = pos[0];

            vector<int> seen(map.size() * width, 0);
            while (y < map.size() && x < map[y].size() && y >= 0 && x >= 0) {
                int newX = x + dirs[dirNum][1];
                int newY = y + dirs[dirNum][0];
                if (newY < map.size() && newX < map[y].size() && newY >= 0 && newX >= 0) {
                    if (map[newY][newX].isObstacle) {
                        int state = (y * width + x);
                        if (seen[state] == trial) {
                            // This position has appeared before, so guard must be in a loop
                            numSuccessfulPositions++;
                            break;
                        }
                        seen[state] = trial;
                    }
                    while (map[newY][newX].isObstacle) {
                        dirNum = (dirNum+1) % 4;
                        newX = x + dirs[dirNum][1];
                        newY = y + dirs[dirNum][0];
                    }
                    x = newX;
                    y = newY;
                } else {
                    break;
                }
            }
            // reset it
            map[obstacleY][obstacleX].isObstacle = false;
        }
    }

    std::cout << numSuccessfulPositions << endl;

    return EXIT_SUCCESS;
}