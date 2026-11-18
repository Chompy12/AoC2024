#include "part1.h"

struct Tile {
    bool isObstacle = false;
    bool isVisited = false;
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
            row.push_back({true, false});
            x++;
        } else if (tile == '^') {
            pos[1] = x;
            pos[0] = y;
            row.push_back({false, true});
            x++;
        } else {
            row.push_back({false, false});
            x++;
        }
    }
    map.push_back(row);

    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dirNum = 0;

    x = pos[1];
    y = pos[0];

    int visited = 1;
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
                visited++;
                map[y][x].isVisited = true;
            }
        } else {
            break;
        }
    }

    cout << visited << endl;

    return EXIT_SUCCESS;
}