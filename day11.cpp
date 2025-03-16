#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Pair
{
    int chip;
    int generator;
    string c;

    bool operator<(const Pair &other) const
    {
        if (chip != other.chip)
        {
            return chip < other.chip;
        }
        return generator < other.generator;
    }
};

struct State
{
    vector<Pair> items;

    bool valid()
    {
        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].chip == items[i].generator)
            {
                continue;
            }

            for (int j = 0; j < items.size(); j++)
            {
                if (i == j)
                {
                    continue;
                }
                if (items[i].chip == items[j].generator)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool is_end_pos() const
    {
        for (auto &i : items)
        {
            if (i.chip != 4 || i.generator != 4)
            {
                return false;
            }
        }

        return true;
    }

    bool operator==(const State &other) const
    {
        if (items.size() != items.size())
        {
            return false;
        }

        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].chip != other.items[i].chip)
            {
                return false;
            }
            if (items[i].generator != other.items[i].generator)
            {
                return false;
            }
        }

        return true;
    }
};

template <>
struct std::hash<std::pair<State, int>>
{
    size_t operator()(const std::pair<State, int> &k) const
    {
        size_t hash = k.second;

        for (auto &s : k.first.items)
        {
            hash <<= 2;
            hash |= s.chip;
            hash <<= 2;
            hash |= s.generator;
        }

        return hash;
    }
};

void part1()
{
    int64_t result = 0;
    ifstream file("input11.txt");

    string line;
    int floor = 1;
    State init_state;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        cout << "new floor" << floor << endl;

        bool newword = true;
        while (newword)
        {
            newword = false;
            while (ss >> word)
            {
                if (word == "a")
                {
                    newword = true;
                    break;
                }
            }
            if (newword)
            {
                string mat;
                ss >> word;
                mat += word[0];
                mat += word[1];
                mat += word[2];
                cout << mat;
                ss >> word;
                cout << word[0] << endl;

                int index = -1;
                for (int i = 0; i < init_state.items.size(); i++)
                {
                    if (init_state.items[i].c == mat)
                    {
                        index = i;
                        break;
                    }
                }
                if (index == -1)
                {
                    index = init_state.items.size();
                    init_state.items.push_back({0, 0, mat});
                }

                if (word[0] == 'm')
                {
                    init_state.items[index].chip = floor;
                }
                else
                {
                    init_state.items[index].generator = floor;
                }
            }
        }
        floor++;
    }

    sort(init_state.items.begin(), init_state.items.end());

    vector<pair<State, int>> queue;
    queue.push_back({init_state, 1});
    unordered_set<pair<State, int>> seen;
    seen.insert(queue[0]);

    while (true)
    {
        vector<pair<State, int>> newqueue;
        bool found_end = false;

        for (auto q : queue)
        {
            if (q.first.is_end_pos())
            {
                found_end = true;
                break;
            }

            // move up
            if (q.second != 4)
            {
                // single item
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                    if (q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].generator++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                }

                // Two items
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second && q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip++;
                        newstate.items[i].generator++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                    if (q.first.items[i].chip != q.second && q.first.items[i].generator != q.second)
                    {
                        continue;
                    }
                    for (int j = i + 1; j < q.first.items.size(); j++)
                    {
                        if (q.first.items[i].chip == q.second)
                        {
                            if (q.first.items[j].chip == q.second)
                            {
                                State newstate = q.first;
                                newstate.items[i].chip++;
                                newstate.items[j].chip++;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second + 1});
                                    newqueue.push_back({newstate, q.second + 1});
                                }
                            }
                        }
                        if (q.first.items[i].generator == q.second)
                        {
                            if (q.first.items[j].generator == q.second) {
                                State newstate = q.first;
                                newstate.items[i].generator++;
                                newstate.items[j].generator++;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second + 1});
                                    newqueue.push_back({newstate, q.second + 1});
                                }
                            }
                        }
                    }
                }
            }

            // move down
            if (q.second != 1) {
                // single item
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                    if (q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].generator--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                }

                // Two items
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second && q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip--;
                        newstate.items[i].generator--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                    if (q.first.items[i].chip != q.second && q.first.items[i].generator != q.second)
                    {
                        continue;
                    }
                    for (int j = i + 1; j < q.first.items.size(); j++)
                    {
                        if (q.first.items[i].chip == q.second)
                        {
                            if (q.first.items[j].chip == q.second)
                            {
                                State newstate = q.first;
                                newstate.items[i].chip--;
                                newstate.items[j].chip--;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second - 1});
                                    newqueue.push_back({newstate, q.second - 1});
                                }
                            }
                        }
                        if (q.first.items[i].generator == q.second)
                        {
                            if (q.first.items[j].generator == q.second) {
                                State newstate = q.first;
                                newstate.items[i].generator--;
                                newstate.items[j].generator--;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second - 1});
                                    newqueue.push_back({newstate, q.second - 1});
                                }
                            }
                        }
                    }
                }
            }
        }

        if (found_end)
        {
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
    ifstream file("input11.txt");

    string line;
    int floor = 1;
    State init_state;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        cout << "new floor" << floor << endl;

        bool newword = true;
        while (newword)
        {
            newword = false;
            while (ss >> word)
            {
                if (word == "a")
                {
                    newword = true;
                    break;
                }
            }
            if (newword)
            {
                string mat;
                ss >> word;
                mat += word[0];
                mat += word[1];
                mat += word[2];
                cout << mat;
                ss >> word;
                cout << word[0] << endl;

                int index = -1;
                for (int i = 0; i < init_state.items.size(); i++)
                {
                    if (init_state.items[i].c == mat)
                    {
                        index = i;
                        break;
                    }
                }
                if (index == -1)
                {
                    index = init_state.items.size();
                    init_state.items.push_back({0, 0, mat});
                }

                if (word[0] == 'm')
                {
                    init_state.items[index].chip = floor;
                }
                else
                {
                    init_state.items[index].generator = floor;
                }
            }
        }
        floor++;
    }

    init_state.items.push_back({1, 1, "ele"});
    init_state.items.push_back({1, 1, "dil"});
    sort(init_state.items.begin(), init_state.items.end());

    vector<pair<State, int>> queue;
    queue.push_back({init_state, 1});
    unordered_set<pair<State, int>> seen;
    seen.insert(queue[0]);

    while (true)
    {
        vector<pair<State, int>> newqueue;
        bool found_end = false;

        for (auto q : queue)
        {
            if (q.first.is_end_pos())
            {
                found_end = true;
                break;
            }

            // move up
            if (q.second != 4)
            {
                // single item
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                    if (q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].generator++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                }

                // Two items
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second && q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip++;
                        newstate.items[i].generator++;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second + 1});
                            newqueue.push_back({newstate, q.second + 1});
                        }
                    }
                    if (q.first.items[i].chip != q.second && q.first.items[i].generator != q.second)
                    {
                        continue;
                    }
                    for (int j = i + 1; j < q.first.items.size(); j++)
                    {
                        if (q.first.items[i].chip == q.second)
                        {
                            if (q.first.items[j].chip == q.second)
                            {
                                State newstate = q.first;
                                newstate.items[i].chip++;
                                newstate.items[j].chip++;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second + 1});
                                    newqueue.push_back({newstate, q.second + 1});
                                }
                            }
                        }
                        if (q.first.items[i].generator == q.second)
                        {
                            if (q.first.items[j].generator == q.second) {
                                State newstate = q.first;
                                newstate.items[i].generator++;
                                newstate.items[j].generator++;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second + 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second + 1});
                                    newqueue.push_back({newstate, q.second + 1});
                                }
                            }
                        }
                    }
                }
            }

            // move down
            if (q.second != 1) {
                // single item
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                    if (q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].generator--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                }

                // Two items
                for (int i = 0; i < q.first.items.size(); i++)
                {
                    if (q.first.items[i].chip == q.second && q.first.items[i].generator == q.second)
                    {
                        State newstate = q.first;
                        newstate.items[i].chip--;
                        newstate.items[i].generator--;
                        sort(newstate.items.begin(), newstate.items.end());
                        if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                        {
                            seen.insert({newstate, q.second - 1});
                            newqueue.push_back({newstate, q.second - 1});
                        }
                    }
                    if (q.first.items[i].chip != q.second && q.first.items[i].generator != q.second)
                    {
                        continue;
                    }
                    for (int j = i + 1; j < q.first.items.size(); j++)
                    {
                        if (q.first.items[i].chip == q.second)
                        {
                            if (q.first.items[j].chip == q.second)
                            {
                                State newstate = q.first;
                                newstate.items[i].chip--;
                                newstate.items[j].chip--;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second - 1});
                                    newqueue.push_back({newstate, q.second - 1});
                                }
                            }
                        }
                        if (q.first.items[i].generator == q.second)
                        {
                            if (q.first.items[j].generator == q.second) {
                                State newstate = q.first;
                                newstate.items[i].generator--;
                                newstate.items[j].generator--;
                                sort(newstate.items.begin(), newstate.items.end());
                                if (newstate.valid() && seen.find({newstate, q.second - 1}) == seen.end())
                                {
                                    seen.insert({newstate, q.second - 1});
                                    newqueue.push_back({newstate, q.second - 1});
                                }
                            }
                        }
                    }
                }
            }
        }

        if (found_end)
        {
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
