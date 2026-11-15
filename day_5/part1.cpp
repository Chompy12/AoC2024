#include "part1.h"

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

    string line;
    regex rulePattern(R"((\d+)\|(\d+))");
    regex numberPattern(R"(\d+)");

    int sumCenterValues = 0;
    while (getline(input, line)) {
        if (line.empty()) continue;
        smatch match;
        if (regex_match(line, match, rulePattern)) {
            vector<int> rule;
            rule.push_back(stoi(match[1].str()));
            rule.push_back(stoi(match[2].str()));
            Page::addRule(rule);
        } else {
            vector<Page> update;
            for (sregex_iterator it(line.begin(), line.end(), numberPattern), end; it != end; ++it) {
                int value = stoi(it->str());
                Page newPage(value);
                update.push_back(newPage);
            }
            bool validUpdate = true;
            for (int i = 0; i < update.size()-1; i++) {
                for (int j = i + 1; j < update.size(); j++) {
                    validUpdate = (validUpdate && (update[i] < update[j]));
                }
            }
            if (validUpdate) {
                int midIdx = (update.size()-1)/2;
                sumCenterValues += update[midIdx].getPage();
            }
        }
    }

    cout << sumCenterValues << endl;

    return EXIT_SUCCESS;
}