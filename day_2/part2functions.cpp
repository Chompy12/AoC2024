#include "part2.h"

using namespace std;

bool checkSafeStrict(const vector<int>& levels) {
    bool safe = abs(levels[0] - levels[1]) >= 1 && abs(levels[0] - levels[1]) <= 3;

    for (int i = 1; i < levels.size() - 1; i++) {
        if (!safe) break;
        safe = !(levels[i]-levels[i+1] > 0 ^ levels[0]-levels[1] > 0) &&
        (abs(levels[i] - levels[i+1]) >= 1 && abs(levels[i] - levels[i+1]) <= 3);
    }
    
    return safe;
}

bool checkSafeDampener(const vector<int>& levels) {
    // see if it's already safe
    bool safe = checkSafeStrict(levels);

    for (int i = 0; i < levels.size(); i++) {
        // return if safe arrangement found
        if (safe) return true;
        vector<int> newLevels;

        // copy every element over but one
        for (int j = 0; j < levels.size(); j++) {
            if (j != i) {
                newLevels.push_back(levels[j]);
            }
        }

        // see if removing that one made it safe
        safe = safe || checkSafeStrict(newLevels);
    }

    return safe;
}