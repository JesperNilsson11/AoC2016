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

int day10() {
	long long result = 0;
	ifstream input("input10.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<string> instructions;
		unordered_map<int, vector<int>> bots;
		unordered_map<int, int> output;

		while (getline(input, s)) {
			instructions.push_back(s);
		}

		while (instructions.size()) {
			for (int i = 0; i < instructions.size(); i++) {
				stringstream ss(instructions[i]);
				string ins;

				ss >> ins;

				if (ins == "value") {
					int val;
					int botid;
					ss >> val;
					ss >> ins;
					ss >> ins;
					ss >> ins;
					ss >> botid;

					auto& v = bots[botid];

					if (v.size() < 2)
						v.push_back(val);
					else
						continue;

					instructions.erase(instructions.begin() + i);
					break;
				}
				else {
					int botid1, botid2, botid3;
					string type1, type2;

					ss >> botid1;
					ss >> ins;
					ss >> ins;
					ss >> ins;
					ss >> type1;
					ss >> botid2;
					ss >> ins;
					ss >> ins;
					ss >> ins;
					ss >> type2;
					ss >> botid3;

					if (bots[botid1].size() == 2) {
						sort(bots[botid1].begin(), bots[botid1].end());

						// PART 1
						//if (bots[botid1][0] == 17 && bots[botid1][1] == 61)
						//	return botid1;
						if (type1 == "bot") {
							if (bots[botid2].size() == 2) {
								cout << "warning";
							}
							else {
								bots[botid2].push_back(bots[botid1][0]);
							}
						}
						else {
							output[botid2] = bots[botid1][0];
						}

						if (type2 == "bot") {
							if (bots[botid3].size() == 2) {
								cout << "warning";
							}
							else {
								bots[botid3].push_back(bots[botid1][1]);
							}
						}
						else {
							output[botid3] = bots[botid1][1];
						}

						instructions.erase(instructions.begin() + i);
						break;
					}
				}
			}
		}

		result = output[0] * output[1] * output[2];
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}