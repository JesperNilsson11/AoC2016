#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node
{
    int x;
    int y;
    int size;
    int used;
    int avail;

    bool operator==(const Node &o) const
    {
        return x == o.x && y == o.y && used == o.used && avail == o.avail;
    }

    bool operator!=(const Node &o) const
    {
        return !(*this == o);
    }
};

template <>
struct std::hash<tuple<int, int, int, int>>
{
    size_t operator()(const tuple<int, int, int, int> &k) const
    {
        size_t res = get<0>(k) << 24 | get<1>(k) << 16 | get<2>(k) << 8 | get<3>(k);

        return res;
    }
};

void part1()
{
    int64_t result = 0;
    ifstream file("input22.txt");

    string line;
    getline(file, line);
    getline(file, line);
    vector<Node> nodes;
    while (getline(file, line))
    {
        int x;
        int y;
        int size;
        int used;
        int avail;

        sscanf(line.c_str(), "/dev/grid/node-x%d-y%d %dT %dT %dT", &x, &y, &size, &used, &avail);
        // cout << "x: " << x << " y: " << y << " " << size << " " << used << " " << avail << endl;
        nodes.push_back({x, y, size, used, avail});
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = 0; j < nodes.size(); j++)
        {
            if (nodes[i].used > 0 && i != j && nodes[i].used <= nodes[j].avail)
            {
                result++;
            }
        }
    }

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input22.txt");

    string line;
    getline(file, line);
    getline(file, line);
    vector<Node> nodes;
    int xmax = 0;
    int ymax = 0;
    int min_size = 1000;
    pair<int, int> empty;
    while (getline(file, line))
    {
        int x;
        int y;
        int size;
        int used;
        int avail;

        sscanf(line.c_str(), "/dev/grid/node-x%d-y%d %dT %dT %dT", &x, &y, &size, &used, &avail);
        nodes.push_back({x, y, size, used, avail});
        if (x > xmax)
        {
            xmax = x;
        }
        if (y > ymax)
        {
            ymax = y;
        }

        if (used == 0)
        {
            empty = {x, y};
        }

        if (min_size > size) {
            min_size = size;
        }
    }

    vector<vector<bool>> grid;
    for (int y = 0; y <= ymax; y++)
    {
        grid.push_back(vector<bool>(xmax + 1));
    }

    for (auto &n : nodes)
    {
        grid[n.y][n.x] = (n.used <= min_size) ? true : false;
    }

    unordered_map<tuple<int, int, int, int>, int64_t> seen;
    seen[{empty.first, empty.second, xmax, 0}] = 0;
    vector<pair<tuple<int, int, int, int>, int>> queue;
    queue.push_back({{empty.first, empty.second, xmax, 0}, 0});

    while (queue.size() > 0)
    {
        sort(queue.begin(), queue.end(), [](const pair<tuple<int, int, int, int>, int> &a, const pair<tuple<int, int, int, int>, int> &b)
             {
            int acost = a.second + get<2>(a.first) + get<3>(a.first);
            int bcost = b.second + get<2>(b.first) + get<3>(b.first);
            return acost > bcost;
            });
        auto q = queue.back();
        queue.pop_back();
        bool found = false;

        if (get<2>(q.first) == 0 && get<3>(q.first) == 0)
        {
            found = true;
            result = q.second;
            break;
        }

        for (auto p : vector<pair<int, int>>{{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
        {
            int nx = get<0>(q.first);
            int ny = get<1>(q.first);
            int x = nx + p.first;
            int y = ny + p.second;

            if (x < 0 || x > xmax || y < 0 || y > ymax)
            {
                continue;
            }
            if (grid[y][x] == false)
            {
                continue;
            }
            pair<int, int> empty = {x, y};
            pair<int, int> data = {get<2>(q.first), get<3>(q.first)};

            if (get<2>(q.first) == x && get<3>(q.first) == y)
            {
                data = {nx, ny};
            }

            if (seen.find({empty.first, empty.second, data.first, data.second}) == seen.end())
            {
                seen[{empty.first, empty.second, data.first, data.second}] = q.second + 1;
                queue.push_back({{empty.first, empty.second, data.first, data.second}, q.second + 1});
            }
            else
            {
                if (seen[{empty.first, empty.second, data.first, data.second}] > q.second + 1)
                {
                    cout << "rejected better path" << endl;
                }
            }
        }
    }

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
