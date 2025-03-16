#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "AdventofCode2016/md5.cpp"

using namespace std;

void part1()
{
    int64_t result = 0;
    string input = "ngcjuoqr";

    vector<string> md5s;
    for (int i = 0; i < 1000; i++)
    {
        md5s.push_back(md5(input + to_string(i)));
    }

    int64_t keys = 0;
    while (keys < 64)
    {
        md5s.push_back(md5(input + to_string(result + 1000)));
        string md5_string = md5s[result];

        bool found_key = false;
        char c;
        for (int i = 0; i < md5_string.size() - 2; i++)
        {
            if (md5_string[i] == md5_string[i + 1] && md5_string[i] == md5_string[i + 2])
            {
                found_key = true;
                c = md5_string[i];
                break;
            }
        }

        if (found_key)
        {
            found_key = false;
            for (int i = result + 1; i < result + 1001; i++)
            {
                for (int j = 0; j < md5s[i].size() - 4; j++)
                {
                    if (md5s[i][j] == c &&
                        md5s[i][j + 1] == c &&
                        md5s[i][j + 2] == c &&
                        md5s[i][j + 3] == c &&
                        md5s[i][j + 4] == c)
                    {
                        found_key = true;
                        break;
                    }
                }
            }

            if (found_key)
            {
                keys++;
            }
        }
        result++;
    }

    cout << "part1: " << result - 1 << endl;
}

void part2()
{
    int64_t result = 0;
    string input = "ngcjuoqr";
    //string input = "abc";

    vector<pair<string, int64_t>> md5s;
    for (int i = 0; i < 1001; i++)
    {
        md5s.push_back({"", -1});
    }

    int64_t keys = 0;
    while (keys < 64)
    {
        string md5_string;
        if (md5s[result % 1001].second != result)
        {
            string hash = md5(input + to_string(result));
            for (int j = 0; j < 2016; j++)
            {
                hash = md5(hash);
            }
            md5s[result % 1001] = {hash, result};
        }
        md5_string = md5s[result % 1001].first;

        bool found_key = false;
        char c;
        for (int i = 0; i < md5_string.size() - 2; i++)
        {
            if (md5_string[i] == md5_string[i + 1] && md5_string[i] == md5_string[i + 2])
            {
                found_key = true;
                c = md5_string[i];
                break;
            }
        }

        if (found_key)
        {
            found_key = false;
            for (int i = result + 1; i < result + 1001; i++)
            {
                if (md5s[i % 1001].second != i)
                {
                    string hash = md5(input + to_string(i));

                    for (int j = 0; j < 2016; j++)
                    {
                        hash = md5(hash);
                    }
                    md5s[i % 1001] = {hash, i};
                }
                for (int j = 0; j < md5s[i % 1001].first.size() - 4; j++)
                {
                    if (md5s[i % 1001].first[j] == c &&
                        md5s[i % 1001].first[j + 1] == c &&
                        md5s[i % 1001].first[j + 2] == c &&
                        md5s[i % 1001].first[j + 3] == c &&
                        md5s[i % 1001].first[j + 4] == c)
                    {
                        found_key = true;
                        break;
                    }
                }
            }

            if (found_key)
            {
                keys++;
            }
        }
        result++;
    }

    cout << "part2: " << result - 1 << endl;
}

int main()
{
    part1();
    part2();
}
