#include "part1.h"

using namespace std;

int main() {
    ifstream readFile("read_file.txt");
    if (!readFile) {
        cerr << "Could not open read_file.txt\n";
        return EXIT_FAILURE;
    }
    string filename;
    readFile >> filename;

    ifstream input(filename);
    if (!input) {
        cerr << "Could not open " << filename << "\n";
        return EXIT_FAILURE;
    }

    vector<char> xmas = {'X', 'M', 'A', 'S'};

    char letter;
    vector<vector<char>> crossword;
    vector<char> line;

    while (input.get(letter)) {
        if (letter == '\n') {
            crossword.push_back(line);
            line.clear();
        } else {
            line.push_back(letter);
        }
    }
    crossword.push_back(line);

    int numXMAS = 0;

    for (int y = 0; y < crossword.size(); y++) {
        for (int x = 0; x < crossword[y].size(); x++) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dist = 0; dist <= xmas.size(); dist++) {
                        if (dist == xmas.size()) {
                            numXMAS++;
                            break;
                        }
                        int newY = y + dy * dist;
                        int newX = x + dx * dist;
                        if (!(newY >= 0 && newY < crossword.size())) break;
                        
                        if (!(newX >= 0 && newX < crossword[newY].size())) break;
                        
                        if (crossword[newY][newX] != xmas[dist]) break;
                    }
                }
            }
        }
    }

    cout << numXMAS << endl;

    return EXIT_SUCCESS;
}