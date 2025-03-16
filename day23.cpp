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
    ifstream file("input23.txt");
    vector<tuple<string, string, string>> program;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        program.push_back({});

        ss >> get<0>(program.back());
        ss >> get<1>(program.back());
        ss >> get<2>(program.back());
    }

    int64_t a = 7;
    int64_t b = 0;
    int64_t c = 0;
    int64_t d = 0;
    int64_t pc = 0;
    while (pc >= 0 && pc < program.size()) {
        string inst = get<0>(program[pc]);
        if (inst == "cpy") {
            int64_t *res = &a;
            int64_t src = 0;
            string in_reg = get<1>(program[pc]);
            string out_reg = get<2>(program[pc]);
            bool valid = true;
            if (out_reg == "a") {
                res = &a;
            } else if (out_reg == "b") {
                res = &b;
            } else if (out_reg == "c") {
                res = &c;
            } else if (out_reg == "d") {
                res = &d;
            } else {
                valid = false;
            }

            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            if (valid) {
                *res = src;
            }
        } else if (inst == "inc") {
            string in_reg = get<1>(program[pc]);

            if (in_reg == "a") {
                a++;
            } else if (in_reg == "b") {
                b++;
            } else if (in_reg == "c") {
                c++;
            } else if (in_reg == "d") {
                d++;
            } else {
                cout << "maybe inc error" << endl;
            }
        } else if (inst == "dec") {
            string in_reg = get<1>(program[pc]);

            if (in_reg == "a") {
                a--;
            } else if (in_reg == "b") {
                b--;
            } else if (in_reg == "c") {
                c--;
            } else if (in_reg == "d") {
                d--;
            } else {
                cout << "maybe dec error" << endl;
            }
        } else if (inst == "jnz") {
            int64_t src = 0;
            int64_t jump = 0;
            string in_reg = get<1>(program[pc]);
            string out_reg = get<2>(program[pc]);

            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            if (out_reg == "a") {
                jump = a;
            } else if (out_reg == "b") {
                jump = b;
            } else if (out_reg == "c") {
                jump = c;
            } else if (out_reg == "d") {
                jump = d;
            } else {
                jump = atoi(out_reg.c_str());
            }

            if (src != 0) {
                pc += jump - 1;
            }
        } else if (inst == "tgl") {
            int64_t src = 0;
            string in_reg = get<1>(program[pc]);
            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            int target = pc + src;
            if (target >= 0 && target < program.size()) {
                string target_inst = get<0>(program[target]);
                if (target_inst == "inc") {
                    get<0>(program[target]) = "dec";
                } else if (target_inst == "dec" || target_inst == "tgl") {
                    get<0>(program[target]) = "inc";
                } else if (target_inst == "jnz") {
                    get<0>(program[target]) = "cpy";
                } else if (target_inst == "cpy") {
                    get<0>(program[target]) = "jnz";
                } else {
                    cout << "Error" << endl;
                }
            }
        }
        pc++;
    }

    result = a;

    cout << "part1: " << result << endl;
}

void part2()
{
    int64_t result = 0;
    ifstream file("input23.txt");
    vector<tuple<string, string, string>> program;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        program.push_back({});

        ss >> get<0>(program.back());
        ss >> get<1>(program.back());
        ss >> get<2>(program.back());
    }

    int64_t a = 12;
    int64_t b = 0;
    int64_t c = 0;
    int64_t d = 0;
    int64_t pc = 0;
    while (pc >= 0 && pc < program.size()) {
        if (pc > 15) {
            //cout << "debug" << endl;
        }
        string inst = get<0>(program[pc]);
        if (inst == "cpy") {
            int64_t *res = &a;
            int64_t src = 0;
            string in_reg = get<1>(program[pc]);
            string out_reg = get<2>(program[pc]);
            bool valid = true;
            if (out_reg == "a") {
                res = &a;
            } else if (out_reg == "b") {
                res = &b;
            } else if (out_reg == "c") {
                res = &c;
            } else if (out_reg == "d") {
                res = &d;
            } else {
                valid = false;
            }

            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            if (valid) {
                *res = src;
            }
        } else if (inst == "inc") {
            string in_reg = get<1>(program[pc]);

            if (in_reg == "a") {
                a++;
            } else if (in_reg == "b") {
                b++;
            } else if (in_reg == "c") {
                c++;
            } else if (in_reg == "d") {
                d++;
            } else {
                cout << "maybe inc error" << endl;
            }
        } else if (inst == "dec") {
            string in_reg = get<1>(program[pc]);

            if (in_reg == "a") {
                a--;
            } else if (in_reg == "b") {
                b--;
            } else if (in_reg == "c") {
                c--;
            } else if (in_reg == "d") {
                d--;
            } else {
                cout << "maybe dec error" << endl;
            }
        } else if (inst == "jnz") {
            int64_t src = 0;
            int64_t jump = 0;
            string in_reg = get<1>(program[pc]);
            string out_reg = get<2>(program[pc]);

            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            if (out_reg == "a") {
                jump = a;
            } else if (out_reg == "b") {
                jump = b;
            } else if (out_reg == "c") {
                jump = c;
            } else if (out_reg == "d") {
                jump = d;
            } else {
                jump = atoi(out_reg.c_str());
            }

            if (pc == 9) {
                a += b * d;
            }
            else if (src != 0) {
                pc += jump - 1;
            }
        } else if (inst == "tgl") {
            int64_t src = 0;
            string in_reg = get<1>(program[pc]);
            if (in_reg == "a") {
                src = a;
            } else if (in_reg == "b") {
                src = b;
            } else if (in_reg == "c") {
                src = c;
            } else if (in_reg == "d") {
                src = d;
            } else {
                src = atoi(in_reg.c_str());
            }

            int target = pc + src;
            if (target >= 0 && target < program.size()) {
                string target_inst = get<0>(program[target]);
                if (target_inst == "inc") {
                    get<0>(program[target]) = "dec";
                } else if (target_inst == "dec" || target_inst == "tgl") {
                    get<0>(program[target]) = "inc";
                } else if (target_inst == "jnz") {
                    get<0>(program[target]) = "cpy";
                } else if (target_inst == "cpy") {
                    get<0>(program[target]) = "jnz";
                } else {
                    cout << "Error" << endl;
                }
            }
        }
        pc++;
    }

    result = a;

    cout << "part2: " << result << endl;
}

int main()
{
    part1();
    part2();
}
