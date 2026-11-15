#include "part2.h"

vector<Page> kahnSortPages(vector<Page> update) {
    vector<vector<int>> rules = Page::getRules();

    int indegree;
    vector<int> indegrees;
    vector<Page> stack;
    for (int i = 0; i < update.size(); i++) {
        Page currentPage = update[i];
        indegree = 0;
        for (int j = 0; j < rules.size(); j++) {
            vector<int> rule = rules[j];
            if (currentPage == rule[1]) {
                // check if left node is in the update
                for (int k = 0; k < update.size(); k++) {
                    if (update[k] == rule[0]) {
                        indegree++;
                    }
                }
            }
        }
        indegrees.push_back(indegree);
        if (indegree == 0) stack.push_back(currentPage);
    }

    vector<Page> result;
    
    while (stack.size() > 0) {
        Page currentPage = stack.back();
        stack.pop_back();
        result.push_back(currentPage);
        for (int i = 0; i < rules.size(); i++) {
            vector<int> rule = rules[i];
            if (currentPage == rule[0]) {
                for (int j = 0; j < update.size(); j++) {
                    if (update[j] == rule[1]) {
                        indegrees[j]--;
                        if (indegrees[j] == 0) stack.push_back(update[j]);
                    }
                }
            }
        }
    }
    return result;
}