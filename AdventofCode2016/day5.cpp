#include "functions.h"
#include "md5.h"

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1>{}(p.first);
		auto hash2 = hash<T2>{}(p.second);
		return hash1 ^ hash2;
	}
};

int day5() {
	int result = 0;
	ifstream input("input5.txt");
	//ifstream input("test.txt");
	string s = "        ";

	string code = "abbhdwsy";
	for (int i = 0; ; i++) {
		string hash = code + to_string(i);

		string r = md5(hash);
		if (r[0] == '0' && r[1] == '0' && r[2] == '0' && r[3] == '0' && r[4] == '0') {
			//s += r[5];
			int index = r[5] - '0';
			if (index >= 0 && index <= 7 && s[index] == ' ') {
				result++;
				s[index] = r[6];
			}
		}

		if (result == 8)
			break;
	}

	cout << s << endl;

	return result;
}