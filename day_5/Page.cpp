#include "part1.h"

vector<vector<int>> Page::rules;

Page::Page() {
    setPage(0);
}

Page::Page(int _pageNum) {
    setPage(_pageNum);
}

int Page::getPage() const {
    return pageNum;
}
void Page::setPage(int _pageNum) {
    pageNum = _pageNum;
}
void Page::addRule(vector<int> newRule) {
    rules.push_back(newRule);
}
vector<vector<int>> Page::getRules() {
    return rules;
}
bool Page::operator==(int other) const {
    return (pageNum == other);
}
bool Page::operator==(const Page& other) const {
    return (other == getPage());
}
bool Page::operator<(const Page& other) const {
    vector<int> rule;
    for (int i = 0; i < rules.size(); i++) {
        rule = rules[i];
        if (getPage() == rule[0] && other == rule[1]) {
            return true;
        }
        if (getPage() == rule[1] && other == rule[0]) {
            return false;
        }
    }
    return false;
}