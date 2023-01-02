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

int day6() {
	int result = 0;
	ifstream input("input6.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<string> messages;

		while (getline(input, s)) {
			messages.push_back(s);
		}
		string message = "";
		for (int i = 0; i < messages[0].size(); i++) {
			unordered_map<char, int> letters;

			for (auto& s : messages) {
				letters[s[i]]++;
			}

			char c = ' ';
			int min = 100000;

			for (auto& p : letters) {
				if (p.second < min) {
					min = p.second;
					c = p.first;
				}
			}

			message += c;
		}

		cout << message << endl;
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}