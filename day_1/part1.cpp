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

    int left, right;
    vector<int> leftSide;
    vector<int> rightSide;
    // Read the file
    while (input >> left >> right) {
        leftSide.push_back(left);
        rightSide.push_back(right);
    }

    selectSort(leftSide);
    selectSort(rightSide);

    int diff;
    int diffSum = 0;
    for (int i = 0; i < leftSide.size(); i++) {
        diff = abs(leftSide[i] - rightSide[i]);
        diffSum += diff;
    }

    cout << diffSum << endl;

    return EXIT_SUCCESS;
}