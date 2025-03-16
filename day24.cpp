#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

template<>
struct std::hash<pair<pair<int,int>,int>>
{
    size_t operator()(const pair<pair<int,int>,int>& k) const {
        return k.first.first << 16 | k.first.second << 8 | k.second;
    }
};

void part1()
{
    int64_t result = 0;
    ifstream file("input24.txt");
    vector<vector<char>> map;
    string line;
    int y = 0;
    pair<int,int> start;
    int nums = 0;
    while (getline(file, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
            if (line[i] == '0') {
                start = {i, y};
            }
            if (line[i] >= '0' && line[i] <= '9') {
                int tmp = line[i] - '0';
                if (tmp > nums) {
                    nums = tmp;
                }
            }
        }
        map.push_back(row);
        y++;
    }

    unordered_set<pair<pair<int,int>,int>> seen;
    seen.insert({start, 0});
    vector<pair<pair<int,int>,int>> queue;
    queue.push_back({start, 0});
    int done = (1 << nums) - 1;

    while (queue.size()) {
        vector<pair<pair<int,int>,int>> newqueue;
        bool found = false;

        for (auto q : queue) {
            if (q.second == done) {
                found = true;
                break;
            }

            for (auto p : vector<pair<int,int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
                int nx = q.first.first + p.first;
                int ny = q.first.second + p.second;

                if (nx < 0 || nx >= map[0].size() || ny < 0 || ny >= map.size()) {
                    continue;
                }
                if (map[ny][nx] == '#') {
                    continue;
                }

                int tmp = q.second;
                if (map[ny][nx] != '.' && map[ny][nx] > '0') {
                    tmp |= 1 << (map[ny][nx] - '0' - 1);
                }

                if (seen.find({{nx, ny}, tmp}) == seen.end()) {
                    seen.insert({{nx, ny}, tmp});
                    newqueue.push_back({{nx, ny}, tmp});
                }
            }
        }

        if (found) {
            break;
        }
        queue = newqueue;
        result++;
    }

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input24.txt");
    vector<vector<char>> map;
    string line;
    int y = 0;
    pair<int,int> start;
    int nums = 0;
    while (getline(file, line)) {
        vector<char> row;
        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
            if (line[i] == '0') {
                start = {i, y};
            }
            if (line[i] >= '0' && line[i] <= '9') {
                int tmp = line[i] - '0';
                if (tmp > nums) {
                    nums = tmp;
                }
            }
        }
        map.push_back(row);
        y++;
    }

    unordered_set<pair<pair<int,int>,int>> seen;
    seen.insert({start, 0});
    vector<pair<pair<int,int>,int>> queue;
    queue.push_back({start, 0});
    int done = (1 << nums) - 1;

    while (queue.size()) {
        vector<pair<pair<int,int>,int>> newqueue;
        bool found = false;

        for (auto q : queue) {
            if (q.second == done && q.first == start) {
                found = true;
                break;
            }

            for (auto p : vector<pair<int,int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
                int nx = q.first.first + p.first;
                int ny = q.first.second + p.second;

                if (nx < 0 || nx >= map[0].size() || ny < 0 || ny >= map.size()) {
                    continue;
                }
                if (map[ny][nx] == '#') {
                    continue;
                }

                int tmp = q.second;
                if (map[ny][nx] != '.' && map[ny][nx] > '0') {
                    tmp |= 1 << (map[ny][nx] - '0' - 1);
                }

                if (seen.find({{nx, ny}, tmp}) == seen.end()) {
                    seen.insert({{nx, ny}, tmp});
                    newqueue.push_back({{nx, ny}, tmp});
                }
            }
        }

        if (found) {
            break;
        }
        queue = newqueue;
        result++;
    }

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
