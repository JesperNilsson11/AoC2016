#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

void part1()
{
    int64_t result = 0;
    ifstream file("input18.txt");
    string line;
    getline(file, line);

    for (auto c : line) {
        if (c == '.') {
            result++;
        }
    }

    for (int i = 0; i < 39; i++) {
        string newline;
        for (int j = 0; j < line.size(); j++) {
            char left = '.';
            char center = line[j];
            char right = '.';

            if (j > 0) {
                left = line[j-1];
            }
            if (j < line.size() - 1) {
                right = line[j+1];
            }

            if (left == '^' && center == '^' && right != '^' ||
                left != '^' && center == '^' && right == '^' ||
                left == '^' && center != '^' && right != '^' ||
                left != '^' && center != '^' && right == '^') {
                newline.push_back('^');
            } else {
                newline.push_back('.');
                result++;
            }
        }

        line = newline;
    }

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input18.txt");
    string line;
    getline(file, line);

    for (auto c : line) {
        if (c == '.') {
            result++;
        }
    }

    for (int i = 0; i < 400000-1; i++) {
        string newline;
        for (int j = 0; j < line.size(); j++) {
            char left = '.';
            char center = line[j];
            char right = '.';

            if (j > 0) {
                left = line[j-1];
            }
            if (j < line.size() - 1) {
                right = line[j+1];
            }

            if (left == '^' && center == '^' && right != '^' ||
                left != '^' && center == '^' && right == '^' ||
                left == '^' && center != '^' && right != '^' ||
                left != '^' && center != '^' && right == '^') {
                newline.push_back('^');
            } else {
                newline.push_back('.');
                result++;
            }
        }

        line = newline;
    }

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
