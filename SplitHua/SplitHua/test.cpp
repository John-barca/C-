// write your code here cpp
#include <iostream>
#include <string>
#if 1
int main() {
	std::string src;
	while (std::getline(std::cin, src)) {
		std::string shi;
		auto it = src.begin();
		int count = 0; //记录第一个子串的长度
		while (it != src.end()) {
			if (*it == ' ') {
				it++;
				count++;
				break;
			}
			it++;
			count++;
		}
		int sz = src.size() - count;
		for (int i = 0; it != src.end(); i++, it++) {
			shi += *it;
		}
		int result = 0;
		sz += 1;
		while (sz) {
			src.pop_back();
			sz--;
		}
		it = src.begin();
		int i = 0;
		while (it != src.end()) {
			if (*it == shi[i]) {
				it++;
				if (i == shi.size() - 1) {
					result++;
					i = 0;
					continue;
				}
				i++;
				continue;
			}
			else {
				i = 0;
			}
			it++;
		}

		std::cout << result << std::endl;

	}

	return 0;
}
#endif
#if 0
int main() {
	std::string str1 = "abcd";
	std::string str2 = "aa";
	str1.substr(1,2);
	

	return 0;
}
#endif
// write your code here cpp
// write your code here cpp
#if 0
#include <iostream>

int main() {
	int from, to;
	long long num[81];
	num[0] = 1;
	num[1] = 1;
	int n = 1;
	for (int i = 2; i < 81; i++) {
		num[i] = num[i - 1] + num[i - 2];
	}
	while (std::cin >> from >> to) {
		long long result = 0;
		for (int i = from; i <= to; i++) {
			result += num[i - 1];
		}
		std::cout << result << std::endl;
	}

	return 0;
}
#endif