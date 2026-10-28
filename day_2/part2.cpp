#include "part2.h"

using namespace std;

int main() {
    // Find which file to read
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

    int numSafeReports = 0;
    string line;
    while (getline(input, line)) {
        istringstream lineStream(line);
        vector<int> levels;
        int level;

        while (lineStream >> level) {
            levels.push_back(level);
        }

        bool safe = checkSafeDampener(levels);

        if (safe) numSafeReports++;
    }

    cout << numSafeReports << endl;

    return EXIT_SUCCESS;
}