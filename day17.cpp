#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "AdventofCode2016/md5.cpp"

using namespace std;

struct Ele {
    int x;
    int y;
    string salt;
};

void part1()
{
    vector<Ele> queue;
    string salt = "mmsxrhfx";
    queue.push_back({0, 0, ""});

    while (queue.size() > 0) {
        vector<Ele> newqueue;

        bool found = false;
        for (auto q : queue) {
            string md = md5(salt + q.salt);

            if (q.x == 3 && q.y == 3) {
                found = true;
                cout << "part1: " << q.salt << endl;
                break;
            }

            if (md[0] > 'a' && md[0] < 'g' && q.y > 0) {
                newqueue.push_back({q.x, q.y-1, q.salt + 'U'});
            }
            if (md[1] > 'a' && md[1] < 'g' && q.y < 3) {
                newqueue.push_back({q.x, q.y+1, q.salt + 'D'});
            }
            if (md[2] > 'a' && md[2] < 'g' && q.x > 0) {
                newqueue.push_back({q.x-1, q.y, q.salt + 'L'});
            }
            if (md[3] > 'a' && md[3] < 'g' && q.x < 3) {
                newqueue.push_back({q.x+1, q.y, q.salt + 'R'});
            }
        }
        if (found) {
            break;
        }
        queue = newqueue;
    }
}

void part2()
{
    int64_t result = 0;
    vector<Ele> queue;
    string salt = "mmsxrhfx";
    queue.push_back({0, 0, ""});

    while (queue.size() > 0) {
        vector<Ele> newqueue;

        bool found = false;
        for (auto q : queue) {
            string md = md5(salt + q.salt);

            if (q.x == 3 && q.y == 3) {
                result = q.salt.size();
                continue;
            }

            if (md[0] > 'a' && md[0] < 'g' && q.y > 0) {
                newqueue.push_back({q.x, q.y-1, q.salt + 'U'});
            }
            if (md[1] > 'a' && md[1] < 'g' && q.y < 3) {
                newqueue.push_back({q.x, q.y+1, q.salt + 'D'});
            }
            if (md[2] > 'a' && md[2] < 'g' && q.x > 0) {
                newqueue.push_back({q.x-1, q.y, q.salt + 'L'});
            }
            if (md[3] > 'a' && md[3] < 'g' && q.x < 3) {
                newqueue.push_back({q.x+1, q.y, q.salt + 'R'});
            }
        }
        if (found) {
            break;
        }
        queue = newqueue;
    }

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
