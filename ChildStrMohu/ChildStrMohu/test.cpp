#include <iostream>
#include <string>

int main() {
	std::string src;
	std::string childs;
	while (std::getline(std::cin, src)) {
		std::getline(std::cin, childs);
		if (childs.size() > src.size()) {
			std::cout << -1 << std::endl;
			continue;
		}

		int count = 0;//记录匹配到源串字符的个数
		int step = 0;//记录每次匹配字符的步数
		int flag = 0;//标记位
		for (int i = 0; i < src.size(); i++) {
			if (src[i] == childs[0]) {
				int j = 0;
				while (i < src.size() && j < childs.size()) {
					if (src[i] == childs[j]) {
						count++;
						i++;
						j++;
						continue;
					}
					if (childs[j] == '?' && src[i] != '\0' && step < 3) {
						if (childs[j + 1] == src[i]) {
							count += step;
							j++;
							continue;
						}
						step++;
						i++;
						continue;
					}
					if (step >= 3) {
						flag = 1;
						break;
					}
				}
				if (j == childs.size() || step >= 3) {
					break;
				}
			}
		}
		if (flag == 1) {
			std::cout << "-1" << std::endl;
		}
		else {
			std::cout << count << std::endl;
		}
	}

	return 0;
}