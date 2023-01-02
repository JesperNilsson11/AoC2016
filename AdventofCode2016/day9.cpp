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

long long rec(string s) {
	long long result = 0;
	stringstream ss(s);
	char c;
	int repeat, len;
	ss >> c;
	ss >> len;
	ss >> c;
	ss >> repeat;
	ss >> c;

	
	int index = 0;
	while (s[index] != ')') {
		index++;
	}
	index++;

	//if (index + len == s.size())
	//	return len * repeat;

	for (int i = index; i < s.size(); i++) {
		if (s[i] == '(') {
			int endindex = i;
			while (s[endindex] != ')')
				endindex++;

			string temp = s.substr(i+1, endindex-i);
			stringstream sss(temp);
			int r, l;
			sss >> l;
			sss >> c;
			sss >> r;

			temp = s.substr(i, l + endindex - i + 1);

			result += rec(temp);
			i = endindex + l;
		}
		else {
			result++;
		}
	}

	result *= repeat;

	return result;
}

int day9() {
	long long result = 0;
	ifstream input("input9.txt");
	//ifstream input("test.txt");
	string s;

	if (input.is_open()) {
		char c;
		string output = "";
		while (getline(input, s)) {
			stringstream ss(s);

			while (ss >> c) {
				if (c == '(') {
					int repeat, len;
					ss >> len;
					ss >> c;
					ss >> repeat;
					ss >> c;

					string temp = "";
					for (int i = 0; i < len; i++) {
						ss >> c;
						temp += c;
					}
					for (int i = 0; i < repeat; i++) {
						//output += temp;
					}

					cout << "(" << len << "x" << repeat << ")" << temp << endl<<endl;

					result += rec("(" + to_string(len) + "x" + to_string(repeat) + ")" + temp);
				}
				else if (c == ' ' || c == '\n') {
					cout << "blankspace\n";
				}
				else {
					output += c;
				}
			}

			result += output.size();
		}

	}
	else {
		cout << "Warning file missing!\n";
	}

	return result;
}