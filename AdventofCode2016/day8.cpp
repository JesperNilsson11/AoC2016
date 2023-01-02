#include "functions.h"

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};

void shiftrow(vector<vector<char>>& screen, int index, int nr) {
	for (int i = 0; i < nr; i++) {
		char c = screen[index][screen[index].size() - 1];

		for (int j = 0; j < screen[index].size(); j++) {
			char temp = screen[index][j];
			screen[index][j] = c;
			c = temp;
		}
	}
}

void shiftcol(vector<vector<char>>& screen, int index, int nr) {
	for (int i = 0; i < nr; i++) {
		char c = screen[screen.size()-1][index];

		for (int j = 0; j < screen.size(); j++) {
			char temp = screen[j][index];
			screen[j][index] = c;
			c = temp;
		}
	}
}

void rect(vector<vector<char>>& screen, int a, int b) {
	for (int y = 0; y < b; y++) {
		for (int x = 0; x < a; x++) {
			screen[y][x] = '#';
		}
	}
}

int day8() {
	int result = 0;
	ifstream input("input8.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<vector<char>> screen;
		vector<char> row(50, '.');
		screen.push_back(row);
		screen.push_back(row);
		screen.push_back(row);
		screen.push_back(row);
		screen.push_back(row);
		screen.push_back(row);

		while (getline(input, s)) {
			stringstream ss(s);
			string instruction;
			ss >> instruction;

			if (instruction == "rect") {
				int a, b;
				char x;
				ss >> a;
				ss >> x;
				ss >> b;

				rect(screen, a, b);
			}
			else if (instruction == "rotate") {
				int index, nr;
				string by;
				char c;
				ss >> instruction;
				ss >> c;
				ss >> c;
				ss >> index;
				ss >> by;
				ss >> nr;
				if (instruction == "row") {
					shiftrow(screen, index, nr);
				}
				else {
					shiftcol(screen, index, nr);
				}
			}
		}

		for (auto& v : screen) {
			for (auto c : v) {
				cout << c;
				if (c == '#')
					result++;
			}
			cout << endl;
		}
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}