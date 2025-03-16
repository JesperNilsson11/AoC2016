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
    int64_t result;
    vector<int64_t> elves;
    int num_elves = 3001330;
    for (int i = 0; i < num_elves; i++) {
        elves.push_back(1);
    }

    while (num_elves > 1)
    {
        num_elves = 0;
        for (int i = 0; i < elves.size(); i++) {
            if (elves[i] > 0) {
                int j = i + 1;
                j %= elves.size();
                while (elves[j] == 0)
                {
                    j++;
                    j %= elves.size();
                }
                
                elves[i] += elves[j];
                elves[j] = 0;
                num_elves++;
                result = i + 1;
            }
        }
    }

    cout << "part1: " << result << endl;
}

void part2() {
    vector<int64_t> elves;
    int num_elves = 3001330;
    elves.reserve(num_elves);
    for (int i = 0; i < num_elves; i++) {
        elves.push_back(i+1);
    }

    while (elves.size() > 1) {
        vector<int64_t> newelves;
        unordered_set<int64_t> remove;
        num_elves = elves.size();

        int i = 0;
        int removed = 0;
        while (i + num_elves / 2 + removed < elves.size()) {
            newelves.push_back(elves[i]);
            remove.insert(i + num_elves / 2 + removed);
            num_elves--;
            removed++;
            i++;
        }

        vector<int64_t> newnewelves;
        while (i < elves.size()) {
            if (remove.find(i) == remove.end()) {
                newnewelves.push_back(elves[i]);
            }
            i++;
        }

        newnewelves.insert(newnewelves.end(), make_move_iterator(newelves.begin()), make_move_iterator(newelves.end()));

        elves = newnewelves;
    }

    cout << "part2: " << elves[0] << endl;
}

int main()
{
    part1();
    part2();
}
