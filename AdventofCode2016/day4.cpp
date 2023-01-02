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

int day4() {
	int result = 0;
	ifstream input("input4.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {

		while (getline(input, s)) {
			int book[256];
			for (int i = 0; i < 256; i++)
				book[i] = 0;
			string id = "";
			string checksum = "";

			bool ifid = false;
			bool ifcheck = false;

			for (auto c : s) {
				if (c >= '0' && c <= '9') {
					ifid = true;
				}
				else if (c == '[') {
					ifid = false;
					ifcheck = true;
					continue;
				}
				else if (c == ']') {
					ifcheck = false;
					continue;
				}
				else if (c == '-') {
					continue;
				}

				if (ifid)
					id += c;
				else if (ifcheck)
					checksum += c;
				else
					book[c]++;
			}

			vector<int> highest;
			for (int i = 0; i < 256; i++)
				highest.push_back(book[i]);

			sort(highest.begin(), highest.end());

			bool legit = true;
			for (int i = 0; i < 5; i++) {
				if (highest[highest.size() - 1 - i] == book[checksum[i]]) {

				}
				else {
					legit = false;
					break;
				}
			}

			if (legit) {
				int nr = stoi(id);
				result += nr;

				int rest = nr % ('z' - 'a' + 1);
				for (auto c : s) {
					if (c == '-')
						cout << " ";
					else {
						c += rest;
						if (c > 'z')
							c -= ('z' - 'a' + 1);
						cout << c;
					}
				}

				cout << nr << endl;
			}
		}
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}