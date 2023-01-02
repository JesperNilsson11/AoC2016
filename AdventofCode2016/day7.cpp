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

int day7() {
	int result = 0;
	ifstream input("input7.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		vector<string> messages;

		while (getline(input, s)) {
			bool insidebracket = false;
			bool foundabba = false;

			vector<string> outside;
			vector<string> inside;
			for (int i = 1; i < s.size()-1; i++) {
				if (s[i] == '[') {
					insidebracket = true;
					continue;
				}
				else if (s[i] == ']') {
					insidebracket = false;
					continue;
				}
				else if (s[i - 1] == s[i + 1] && s[i] != s[i + 1]) {
					string aba = "";
					aba += s[i - 1];
					aba += s[i];
					aba += s[i + 1];

					if (insidebracket) {
						inside.push_back(aba);
					}
					else {
						outside.push_back(aba);
					}
				}
				//else if (s[i] == s[i + 1] && s[i - 1] == s[i + 2] && s[i] != s[i-1]) {
				//	cout << s[i - 1] << s[i] << s[i + 1]<< s[i + 2] << " ";
				//
				//	if (insidebracket) {
				//		foundabba = false;
				//		break;
				//	}
				//
				//	foundabba = true;
				//}
			}

			bool found = false;
			for (auto& aba : outside) {
				for (auto& bab : inside) {
					if (bab[0] == aba[1] && bab[1] == aba[0]) {
						found = true;
						result++;
						break;
					}
				}
				if (found)
					break;
			}

			//if (foundabba) {
			//	result++;
			//	cout << s << endl;
			//}
		}
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}