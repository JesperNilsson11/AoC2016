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

int day1() {
	int result = 0;
	ifstream input("input1.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<pair<char, int>> directions;
		unordered_map<pair<int, int>, int, hash_pair> map;

		while (input >> s) {
			stringstream ss(s);
			char c;
			int num;

			ss >> c;
			ss >> num;

			directions.push_back({ c, num });
		}

		int x = 0;
		int y = 0;
		int dir = 0;
		bool found = false;
		for (auto& p : directions) {
			if (found)
				break;

			if (p.first == 'R') {
				dir++;

				if (dir > 3)
					dir = 0;
			}
			else {
				dir--;
				if (dir < 0)
					dir = 3;
			}

			switch (dir)
			{
			case 0:
				for (int i = 0; i < p.second; i++) {
					y++;
					map[{x, y}]++;

					if (map[{x, y}] == 2) {
						found = true;
						break;
					}
				}
				break;
			case 1:
				for (int i = 0; i < p.second; i++) {
					x++;
					map[{x, y}]++;

					if (map[{x, y}] == 2) {
						found = true;
						break;
					}
				}
				break;
			case 2:
				for (int i = 0; i < p.second; i++) {
					y--;
					map[{x, y}]++;

					if (map[{x, y}] == 2) {
						found = true;
						break;
					}
				}
				break;
			case 3:
				for (int i = 0; i < p.second; i++) {
					x--;
					map[{x, y}]++;

					if (map[{x, y}] == 2) {
						found = true;
						break;
					}
				}
				break;
			default:
				break;
			}


			
		}

		result = abs(x) + abs(y);
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}