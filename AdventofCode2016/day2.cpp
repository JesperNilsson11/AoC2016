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

int day2() {
	int result = 0;
	string code;
	ifstream input("input2.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<string> directions;
		unordered_map<pair<int, int>, char, hash_pair> map;
		map[{0, -2}] = '1';
		map[{-1, -1}] = '2';	map[{0, -1}] = '3';		map[{1, -1}] = '3';
		map[{-2, 0}] = '5';		map[{-1, 0}] = '6';		map[{0, 0}] = '7';		map[{1, 0}] = '8';		map[{2, 0}] = '9';
		map[{-1, 1}] = 'A';		map[{0, 1}] = 'B';		map[{1, 1}] = 'C';
		map[{0, 2}] = 'D';

		while (getline(input, s)) {
			directions.push_back(s);
		}

		int x = -2;
		int y = 0;

		for (auto& s : directions) {

			for (auto c : s) {
				int oldx = x;
				int oldy = y;
				if (c == 'U') {
					y--;
				}
				else if (c == 'R') {
					x++;
				}
				else if (c == 'D') {
					y++;
				}
				else {
					x--;
				}

				if (map.find({ x, y }) == map.end()) {
					x = oldx;
					y = oldy;
				}

			}

			code += map[{x, y}];
			//result *= 10;
			//if (x == 0) {
			//	if (y == 0)
			//		result += 1;
			//	else if (y == 1)
			//		result += 4;
			//	else
			//		result += 7;
			//}
			//else if (x == 1) {
			//	if (y == 0)
			//		result += 2;
			//	else if (y == 1)
			//		result += 5;
			//	else
			//		result += 8;
			//}
			//else {
			//	if (y == 0)
			//		result += 3;
			//	else if (y == 1)
			//		result += 6;
			//	else
			//		result += 9;
			//}
		}

		cout << "code: " << code << endl;
		result = 1;
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}