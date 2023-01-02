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

int day11() {
	long long result = 0;
	ifstream input("input11.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<string> instructions;
		unordered_map<int, vector<int>> bots;
		unordered_map<int, int> output;

		while (getline(input, s)) {
			instructions.push_back(s);
		}

	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}