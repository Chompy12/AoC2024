#include "part1.h"

using namespace std;

void selectSort(vector<int> &values) {
    int min;
    int min_idx;
    for (int i = 0; i < values.size(); i++) {
        min = 999999999;
        min_idx = i;
        for (int j = i; j < values.size(); j++) {
            if (values[j] < min) {
                min = values[j];
                min_idx = j;
            }
        }
        values[min_idx] = values[i];
        values[i] = min;
    }
}