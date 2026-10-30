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

    string text{
        istreambuf_iterator<char>(input),
        istreambuf_iterator<char>()
    };

    std::regex pattern(R"(mul\((\d+),(\d+)\))");

    int mulSum = 0;

    const auto end = std::sregex_iterator{};
    for (auto it = std::sregex_iterator(text.cbegin(), text.cend(), pattern); it != end; ++it) {
        const std::smatch& match = *it;
        int num1 = stoi(match[1].str()); int num2 = stoi(match[2].str());
        mulSum += num1 * num2;
    }

    cout << mulSum << endl;

    return EXIT_SUCCESS;
}