#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

string rotate(string password, int start)
{
    if (start < 0)
    {
        while (start < 0)
        {
            start += password.size();
        }
    }
    if (start >= password.size())
    {
        while (start >= password.size())
        {
            start -= password.size();
        }
    }
    string newpass;
    for (int i = start; i < password.size(); i++)
    {
        newpass.push_back(password[i]);
    }
    for (int i = 0; i < start; i++)
    {
        newpass.push_back(password[i]);
    }

    return newpass;
}

void part1()
{
    ifstream file("input21.txt");

    string password = "abcdefgh";
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string word;
        ss >> word;

        if (word == "rotate")
        {
            ss >> word;
            if (word == "left" || word == "right")
            {
                int steps;
                ss >> steps;

                int start = word == "left" ? steps : password.size() - steps;
                password = rotate(password, start);
            }
            else
            {
                ss >> word;
                ss >> word;
                ss >> word;
                ss >> word;

                char c;
                ss >> c;
                int index;
                for (int i = 0; i < password.size(); i++)
                {
                    if (c == password[i])
                    {
                        index = i;
                        break;
                    }
                }

                int steps = 1 + index + (index >= 4 ? 1 : 0);
                password = rotate(password, password.size() - steps);
            }
        }
        else if (word == "swap")
        {
            ss >> word;
            if (word == "position")
            {
                int index1;
                int index2;
                ss >> index1;
                ss >> word;
                ss >> word;
                ss >> index2;

                char tmp = password[index1];
                password[index1] = password[index2];
                password[index2] = tmp;
            }
            else
            {
                char x;
                char y;
                ss >> x;
                ss >> word;
                ss >> word;
                ss >> y;

                for (int i = 0; i < password.size(); i++)
                {
                    if (password[i] == x)
                    {
                        password[i] = y;
                    }
                    else if (password[i] == y)
                    {
                        password[i] = x;
                    }
                }
            }
        }
        else if (word == "reverse")
        {
            int index1;
            int index2;
            ss >> word;
            ss >> index1;
            ss >> word;
            ss >> index2;
            while (index1 < index2)
            {
                char c;
                c = password[index1];
                password[index1] = password[index2];
                password[index2] = c;
                index1++;
                index2--;
            }
        }
        else if (word == "move")
        {
            int index1;
            int index2;
            ss >> word;
            ss >> index1;
            ss >> word;
            ss >> word;
            ss >> index2;

            string newpass;
            for (int i = 0; i < password.size(); i++)
            {
                if (i == index1)
                {
                    continue;
                }
                if (i == index2)
                {
                    if (index1 < index2)
                    {
                        newpass.push_back(password[i]);
                        newpass.push_back(password[index1]);
                    }
                    else
                    {
                        newpass.push_back(password[index1]);
                        newpass.push_back(password[i]);
                    }
                }
                else
                {
                    newpass.push_back(password[i]);
                }
            }

            password = newpass;
        }
    }

    cout << "part1: " << password << endl;
}

void part2()
{
    ifstream file("input21.txt");

    string password = "fbgdceah";
    string line;

    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    reverse(lines.begin(), lines.end());
    for (auto line : lines)
    {
        stringstream ss(line);
        string word;
        ss >> word;

        if (word == "rotate")
        {
            ss >> word;
            if (word == "left" || word == "right")
            {
                int steps;
                ss >> steps;

                int start = word == "left" ? password.size() - steps : steps;
                password = rotate(password, start);
            }
            else
            {
                ss >> word;
                ss >> word;
                ss >> word;
                ss >> word;

                char c;
                ss >> c;

                string testpass = password;
                string newpassword;
                do
                {
                    testpass = rotate(testpass, 1);

                    int index;
                    for (int i = 0; i < testpass.size(); i++)
                    {
                        if (c == testpass[i])
                        {
                            index = i;
                            break;
                        }
                    }

                    int steps = 1 + index + (index >= 4 ? 1 : 0);
                    newpassword = rotate(testpass, testpass.size() - steps);
                } while (newpassword != password);
                password = testpass;
            }
        }
        else if (word == "swap")
        {
            ss >> word;
            if (word == "position")
            {
                int index1;
                int index2;
                ss >> index1;
                ss >> word;
                ss >> word;
                ss >> index2;

                char tmp = password[index1];
                password[index1] = password[index2];
                password[index2] = tmp;
            }
            else
            {
                char x;
                char y;
                ss >> x;
                ss >> word;
                ss >> word;
                ss >> y;

                for (int i = 0; i < password.size(); i++)
                {
                    if (password[i] == x)
                    {
                        password[i] = y;
                    }
                    else if (password[i] == y)
                    {
                        password[i] = x;
                    }
                }
            }
        }
        else if (word == "reverse")
        {
            int index1;
            int index2;
            ss >> word;
            ss >> index1;
            ss >> word;
            ss >> index2;
            while (index1 < index2)
            {
                char c;
                c = password[index1];
                password[index1] = password[index2];
                password[index2] = c;
                index1++;
                index2--;
            }
        }
        else if (word == "move")
        {
            int index1;
            int index2;
            ss >> word;
            ss >> index2;
            ss >> word;
            ss >> word;
            ss >> index1;

            string newpass;
            for (int i = 0; i < password.size(); i++)
            {
                if (i == index1)
                {
                    continue;
                }
                if (i == index2)
                {
                    if (index1 < index2)
                    {
                        newpass.push_back(password[i]);
                        newpass.push_back(password[index1]);
                    }
                    else
                    {
                        newpass.push_back(password[index1]);
                        newpass.push_back(password[i]);
                    }
                }
                else
                {
                    newpass.push_back(password[i]);
                }
            }

            password = newpass;
        }
    }

    cout << "part2: " << password << endl;
}

int main()
{
    part1();
    part2();
}
