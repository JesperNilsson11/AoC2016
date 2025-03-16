#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

bool is_wall(int64_t x, int64_t y, int64_t fav) {
    int64_t res = x*x + 3*x + 2*x*y + y + y*y + fav;
    int64_t num_ones = 0;

    while (res > 0) {
        if (res & 1 == 1) {
            num_ones++;
        }
        res >>= 1;
    }

    return num_ones % 2 == 1;
}

template<>
struct std::hash<pair<int64_t, int64_t>>
{
    size_t operator()(const pair<int64_t, int64_t>& k) const {
        return k.first << 32 | k.second;
    }
};

void part1()
{
    int64_t result = 0;
    int64_t favorite_number = 1364;

    vector<pair<int64_t, int64_t>> queue;
    unordered_set<pair<int64_t, int64_t>> seen;
    seen.insert({1, 1});
    queue.push_back({1, 1});

    while (queue.size() > 0)
    {
        vector<pair<int64_t, int64_t>> newqueue;

        bool found = false;
        for (auto q : queue) {
            if (q.first == 31 && q.second == 39) {
                found = true;
                break;
            }

            for (auto d : vector<pair<int,int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
                int64_t nx = q.first + d.first;
                int64_t ny = q.second + d.second;

                if (nx < 0 || ny < 0) {
                    continue;
                }
                if (is_wall(nx, ny, favorite_number)) {
                    continue;
                }
                if (seen.find({nx, ny}) != seen.end()) {
                    continue;
                }

                seen.insert({nx, ny});
                newqueue.push_back({nx, ny});
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
    int64_t favorite_number = 1364;

    vector<pair<int64_t, int64_t>> queue;
    unordered_set<pair<int64_t, int64_t>> seen;
    seen.insert({1, 1});
    queue.push_back({1, 1});

    for (int i = 0; i < 50; i++)
    {
        vector<pair<int64_t, int64_t>> newqueue;

        for (auto q : queue) {
            for (auto d : vector<pair<int,int>>{{1,0}, {-1,0}, {0,1}, {0,-1}}) {
                int64_t nx = q.first + d.first;
                int64_t ny = q.second + d.second;

                if (nx < 0 || ny < 0) {
                    continue;
                }
                if (is_wall(nx, ny, favorite_number)) {
                    continue;
                }
                if (seen.find({nx, ny}) != seen.end()) {
                    continue;
                }

                seen.insert({nx, ny});
                newqueue.push_back({nx, ny});
            }
        }

        queue = newqueue;
    }

    result = seen.size();

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
