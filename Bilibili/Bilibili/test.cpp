//#include <iostream>
//#include <string>
//#include <vector>
//
//int main() {
//	std::string str;
//	while (std::getline(std::cin, str)) {
//		int count = 0; // 记录程序中空格的个数
//		auto it = str.begin();
//		while (it != str.end()) {
//			if (*it == ' ') {
//				count++;
//			}
//			it++;
//		}
//
//		std::vector<std::string> Num;
//		Num.resize(++count);
//
//		std::string result;
//		result = "";
//		int j = 0;
//		for (int i = 0; i < str.size(); i++) {
//			if (str[i] != ' ') {
//				result += str[i];
//			}
//			else {
//				Num[j++] = result;
//				result = "";
//			}
//
//			if (i + 1 == str.size()) {
//				Num[j++] = result;
//				result = "";
//			}
//		}
//		
//		for (int i = Num.size() - 1; i > 0; i--) {
//			std::cout << Num[i] << " ";
//		}
//		std::cout << Num[0] << std::endl;
//	}
//
//	return 0;
//}

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main() {
	std::string str;
	std::vector<std::string> Num;
	while (std::getline(std::cin, str)) {
		int count = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ',') {
				count++;
			}
		}
		Num.resize(++count);
		
		auto it = str.begin();
		std::string result = "";
		int j = 0;
		while (it != str.end()) {
			if (*it == ',') {
				Num[j++] = result;
				result = "";
				it++;
				continue;
			}
			else {
				result += *it;
			}

			if (it + 1 == str.end()) {
				Num[j++] = result;
				result = "";
			}
			it++;
		}

		std::vector<int> result;
		result.resize(count);
		std::string min = Num[0];
		for (int i = 0; i < Num.size() - 1; i++) {
			if (i + 1 < Num.size()) {
				std::string stmp1 = Num[i + 1] + min;
				std::string stmp2 = min + Num[i + 1];
				int tmp1 = stoi(stmp1, 0, 10);
				int tmp2 = stoi(stmp2, 0, 10);
				if (tmp1 > tmp2) {
					min = min + Num[i + 1];
				}
				else {
					min = Num[i + 1] + min;
				}
			}
		}

		std::cout << min << std::endl;

	}

	return 0;
}