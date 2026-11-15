#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <iterator>

using namespace std;

class Page {
    private:
        int pageNum;
        static vector<vector<int>> rules;
    public:
        Page();
        Page(int);
        int getPage() const;
        void setPage(int);
        static void addRule(vector<int>);
        static vector<vector<int>> getRules();
        bool operator<(const Page&) const;
        bool operator==(int) const;
        bool operator==(const Page&) const;
};