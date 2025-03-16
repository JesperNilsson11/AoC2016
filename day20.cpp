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
    ifstream file("input20.txt");

    string line;
    vector<pair<int64_t, int64_t>> ranges;
    while (getline(file, line))
    {
        stringstream ss(line);
        int64_t max;
        int64_t min;

        ss >> min;
        char c;
        ss >> c;
        ss >> max;
        // cout << "range: " << min << " - " << max << endl;
        ranges.push_back({min, max});
    }

    bool newval = true;
    while (newval)
    {
        newval = false;
        for (auto &r : ranges)
        {
            if (result >= r.first && result <= r.second)
            {
                newval = true;
                result = r.second + 1;
            }
        }
    }

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input20.txt");

    string line;
    vector<pair<int64_t, int64_t>> ranges;
    while (getline(file, line))
    {
        stringstream ss(line);
        int64_t max;
        int64_t min;

        ss >> min;
        char c;
        ss >> c;
        ss >> max;
        // cout << "range: " << min << " - " << max << endl;
        ranges.push_back({min, max});
    }

    sort(ranges.begin(), ranges.end());

    vector<pair<int64_t, int64_t>> newranges;

    newranges.push_back(ranges[0]);

    for (int i = 0; i < ranges.size(); i++)
    {
        if (newranges.back().first > ranges[i].first)
        {
            cout << "Error" << endl;
        }
        if (newranges.back().second >= ranges[i].first)
        {
            newranges.back().second = max(newranges.back().second, ranges[i].second);
        }
        else
        {
            newranges.push_back(ranges[i]);
        }
    }

    ranges = newranges;

    result += ranges[0].first;
    for (int i = 0; i < ranges.size() - 1; i++)
    {
        if (ranges[i].second < ranges[i + 1].first)
        {
            result += ranges[i + 1].first - ranges[i].second - 1;
        }
    }
    result += 4294967295 - ranges.back().second;

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
