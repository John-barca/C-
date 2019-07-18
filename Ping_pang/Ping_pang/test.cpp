//// write your code here cpp
//#include <iostream>
//#include <string>
//
//int main() {
//	std::string Ping_pang;
//	while (std::getline(std::cin, Ping_pang)) {
//		std::string str1 = "";
//		std::string str2 = "";
//		bool flag = false;
//		for (int i = 0; i < Ping_pang.size(); i++) {
//			if (Ping_pang[i] == ' ') {
//				flag = true;
//				continue;
//			}
//			if (flag == false) {
//				str1 += Ping_pang[i];
//			}
//			else {
//				str2 += Ping_pang[i];
//			}
//		}
//		int i = 0;
//		while (str2.size()) {
//			int ret;
//			ret = str1.find(str2[i], 0);
//			if (std::string::npos != ret) {
//				str2.erase(str2.begin() + i);
//				str1.erase(str1.begin() + ret);
//				i = 0;
//				continue;
//			}
//			else {
//				std::cout << "No" << std::endl;
//				break;
//			}
//		}
//		if (str2 == "") {
//			std::cout << "Yes" << std::endl;
//		}
//		else {
//			std::cout << "No" << std::endl;
//		}
//		Ping_pang = "";
//	}
//
//	return 0;
//}

#include <iostream>
#include <string>
#include <map>

int main() {
	std::string str1;
	std::string str2;
	while (std::cin >> str1 >> str2) {
		std::map<char, int> s1;
		std::map<char, int> s2;

		for (int i = 0; i < str1.size(); i++) {
			s1[str1[i]]++;
		}

		for (int i = 0; i < str2.size(); i++) {
			s2[str2[i]]++;
		}

		for (int j = 'A'; j <= 'Z'; j++) {
			if (s2[j] > s1[j]) {
				std::cout << "No" << std::endl;
				break;
			}
			if (j == 'Z') {
				std::cout << "Yes" << std::endl;
			}
		}
	}

	return 0;
}