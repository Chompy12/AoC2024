#include "part1.h"

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

        bool safe = abs(levels[0] - levels[1]) >= 1 && abs(levels[0] - levels[1]) <= 3;

        for (int i = 1; i < levels.size() - 1; i++) {
            if (!safe) break;
            safe = !(levels[i]-levels[i+1] > 0 ^ levels[0]-levels[1] > 0) &&
             (abs(levels[i] - levels[i+1]) >= 1 && abs(levels[i] - levels[i+1]) <= 3);
        }
        
        if (safe) numSafeReports++;
    }

    cout << numSafeReports << endl;

    return EXIT_SUCCESS;
}