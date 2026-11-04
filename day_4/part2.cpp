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

    int numX_MAS = 0;

    for (int y = 1; y < crossword.size()-1; y++) {
        for (int x = 1; x < crossword[y].size()-1; x++) {
            if (crossword[y][x] == 'A') {
                char letter1 = crossword[y-1][x-1];
                if (letter1 == 'M' || letter1 == 'S') {
                    char letter2 = crossword[y+1][x+1];
                    if ((letter2 == 'M' || letter2 == 'S') && letter2 != letter1) {
                        if ((crossword[y-1][x+1] == letter1 && crossword[y+1][x-1] == letter2) || (crossword[y-1][x+1] == letter2 && crossword[y+1][x-1] == letter1)) {
                            numX_MAS++;
                        }
                    }
                }
            }
        }
    }

    cout << numX_MAS << endl;

    return EXIT_SUCCESS;
}