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
    string a = "11011110011011101";
    int disk_size = 272;

    while (a.size() < disk_size) {
        string b = a;
        reverse(b.begin(), b.end());
        for (int i = 0; i < b.size(); i++) {
            b[i] = b[i] == '1' ? '0' : '1';
        }

        a = a + '0' + b;
    }

    string check_sum;
    for (int i = 0; i < disk_size; i++) {
        check_sum.push_back(a[i]);
    }

    while (check_sum.size() % 2 == 0) {
        string new_check_sum;
        for (int i = 0; i < check_sum.size() - 1; i += 2) {
            if (check_sum[i] == check_sum[i+1]) {
                new_check_sum.push_back('1');
            } else {
                new_check_sum.push_back('0');
            }
        }
        check_sum = new_check_sum;
    }

    cout << "part1: " << check_sum << endl;
}

void part2()
{
    string a = "11011110011011101";
    int disk_size = 35651584;

    while (a.size() < disk_size) {
        string b = a;
        reverse(b.begin(), b.end());
        for (int i = 0; i < b.size(); i++) {
            b[i] = b[i] == '1' ? '0' : '1';
        }

        a = a + '0' + b;
    }

    string check_sum;
    for (int i = 0; i < disk_size; i++) {
        check_sum.push_back(a[i]);
    }

    while (check_sum.size() % 2 == 0) {
        string new_check_sum;
        for (int i = 0; i < check_sum.size() - 1; i += 2) {
            if (check_sum[i] == check_sum[i+1]) {
                new_check_sum.push_back('1');
            } else {
                new_check_sum.push_back('0');
            }
        }
        check_sum = new_check_sum;
    }

    cout << "part2: " << check_sum << endl;
}

int main()
{
    part1();
    part2();
}
