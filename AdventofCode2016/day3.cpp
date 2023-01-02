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

int day3() {
	int result = 0;
	ifstream input("input3.txt");
	//ifstream input("test.txt");
	string s;
	int num;

	if (input.is_open()) {
		vector<int> tri1;
		vector<int> tri2;
		vector<int> tri3;

		while (input >> num) {
			vector<int> tri;
			tri.push_back(num);
			tri1.push_back(num);

			input >> num;
			tri.push_back(num);
			tri2.push_back(num);

			input >> num;
			tri.push_back(num);
			tri3.push_back(num);

			sort(tri.begin(), tri.end());
			if (tri[0] + tri[1] > tri[2])
				result++;
		}

		result = 0;
		for (int i = 0; i < tri1.size(); i += 3) {
			if (tri1[i] + tri1[i + 1] > tri1[i + 2] && tri1[i+2] + tri1[i + 1] > tri1[i] && tri1[i] + tri1[i + 2] > tri1[i + 1])
				result++;
			if (tri2[i] + tri2[i + 1] > tri2[i + 2]&& tri2[i+2] + tri2[i + 1] > tri2[i]&& tri2[i] + tri2[i + 2] > tri2[i + 1])
				result++;
			if (tri3[i] + tri3[i + 1] > tri3[i + 2] && tri3[i+2] + tri3[i + 1] > tri3[i] && tri3[i] + tri3[i + 2] > tri3[i + 1])
				result++;
		}
	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}