// write your code here cpp
#include <iostream>
#include <string>
#include <vector>

void Judge_The_str(std::string& str) {
	int flag = 0; //标记字符串中是否有,
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',' || str[i] == ' ') {
			flag = 1;
			break;
		}
		else {
			continue;
		}
	}

	if (flag == 1) {
		str.insert(str.begin(), '"');
		str += '"';
	}
}

int main() {
	int n;
	while (std::cin >> n) {
		std::cin.get();
		std::vector<std::string> Name;
		Name.resize(n);
		for (int i = 0; i < n; i++) {
			std::getline(std::cin, Name[i]);
		}

		for (int i = 0; i < n; i++) {
			Judge_The_str(Name[i]);
		}

		for (int i = 0; i < Name.size(); i++) {
			if (i != Name.size() - 1) {
				std::cout << Name[i] << ", ";
			}
			else {
				std::cout << Name[i] << std::endl;
			}
		}
	}
	return 0;
}