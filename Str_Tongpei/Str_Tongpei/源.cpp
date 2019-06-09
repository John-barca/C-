#include <iostream>
#include <string>
using namespace std;

bool Judge_str(string str1, string str2) {
	int i = 0;
	for (int str2_num = 0; str2_num < str2.size(); str2_num++) {
		if (str1[i] != '*' && str1[i] != '?') {
			if (str1[i] != str2[str2_num]) {
				return false;
			}
			i++;
		}
		else if (str1[str2_num] == '?') {
			if ((str2[str2_num] >= '0' && str2[str2_num] <= '9') || (str2[str2_num] >= 'A' && str2[str2_num] <= 'Z')
				|| (str2[str2_num] >= 'a' && str2[str2_num] <= 'z')) {
				i++;
				continue;
			}
			else {
				return false;
			}
		}
		else if (str1[i] == '*') {
			while (str1[i] != str2[str2_num]) {
				if ((str2[str2_num] >= '0' && str2[str2_num] <= '9') || (str2[str2_num] >= 'A' && str2[str2_num] <= 'Z')
					|| (str2[str2_num] >= 'a' && str2[str2_num] <= 'z')) {
					str2_num++;
					i++;
					if (str2_num >= str2.size()) {
						return true;
					}
				}
			}
			if (str1[++i] == str2[str2_num]) {
				i++;
				continue;
			}
		}
	}
	return true;
}

	int main() {
		string str1_with_;
		string str2_;
		while (cin >> str1_with_ >> str2_) {
			bool result = Judge_str(str1_with_, str2_);
			if (result) {
				cout << true << endl;
			}
			else {
				cout << false << endl;
			}
		}
		return 0;
	}