//// write your code here cpp
//#include <iostream>
//#include <string>
//
//int main() {
//	std::string str;
//	std::string temp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	std::string result;
//	while (std::getline(std::cin, str)) {
//		for (int i = 0; i < str.size(); i++) {
//			if (str[i] == '_') {
//				if (str[i + 1] >= 'a' && str[i + 1] <= 'z') {
//					str[i + 1] = temp[str[i + 1] - 'a'];
//					continue;
//				}
//			}
//			result += str[i];
//		}
//		std::cout << result << std::endl;
//		str = "";
//		result = "";
//	}
//
//	return 0;
//}

//#include <string>
//#include <iostream>
//
//int main() {
//	std::string str;
//	while (std::getline(std::cin, str)) {
//		int i = 0;
//		int j = str.size() - 1;
//		while (i < j) {
//			if (i < j) {
//				char tmp = str[j];
//				str[j] = str[i];
//				str[i] = tmp;
//				i++;
//				j--;
//			}
//			else {
//				break;
//			}
//		}
//		//auto it = str.begin();
//		//auto beg = str.begin();
//		//while (it != str.end()) {
//		//	if (*it == ' ' ) {
//		//		if (it - 1 == beg) {
//		//			it++;
//		//			beg = it;
//		//			continue;
//		//		}
//		//		else {
//		//			std::reverse(beg, it - 1);
//		//			beg = ++it;
//		//			if (it == str.end()) {
//		//				break;
//		//			}
//		//			continue;
//		//		}
//		//	}
//		//	it++;
//		//}
//
//
//		std::cout << str << std::endl;
//	}
//
//	return 0;
//}


#include <iostream>
#include <vector>
#include <string>

int main() {
	std::string str;
	while (std::getline(std::cin, str)) {
		std::vector<std::string> result;
		result.clear();
		std::string tmp = "";

		for (int i = 0; i < str.size(); i++) {
			if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
				tmp += str[i];
			}
			else {
				if (!tmp.empty()) {
					result.push_back(tmp);
					tmp = "";
				}
			}
		}

		if (!tmp.empty()) {
			result.push_back(tmp);
		}
		for (int i = result.size() - 1; i > 0; i--) {
			std::cout << result[i] << " ";
		}
		std::cout << result[0] << std::endl;
	}

	return 0;
}