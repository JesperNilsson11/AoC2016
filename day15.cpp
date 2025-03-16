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
    ifstream file("input15.txt");

    string line;
    vector<pair<int, int>> discs;
    while (getline(file, line)) {
        int positions;
        int pos;
        int id;

        sscanf(line.c_str(),"Disc #%d has %d positions; at time=0, it is at position %d", &id, &positions, &pos);
        discs.push_back({pos, positions});
    }

    while (true) {
        bool valid = true;

        for (int i = 0; i < discs.size(); i++) {
            if ((discs[i].first + 1 + i + result) % discs[i].second != 0) {
                valid = false;
                break;
            }
        }

        if (valid) {
            break;
        }
        result++;
    }

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input15.txt");

    string line;
    vector<pair<int, int>> discs;
    while (getline(file, line)) {
        int positions;
        int pos;
        int id;

        sscanf(line.c_str(),"Disc #%d has %d positions; at time=0, it is at position %d", &id, &positions, &pos);
        discs.push_back({pos, positions});
    }
    discs.push_back({0, 11});

    while (true) {
        bool valid = true;

        for (int i = 0; i < discs.size(); i++) {
            if ((discs[i].first + 1 + i + result) % discs[i].second != 0) {
                valid = false;
                break;
            }
        }

        if (valid) {
            break;
        }
        result++;
    }

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}

