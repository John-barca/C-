#include <iostream>
#include <string>
#include <vector>

int main() {
	int n;
	while (std::cin >> n) {
		std::cin.get();
		std::vector<std::string> resp;
		resp.resize(n);
		for (int i = 0; i < resp.size(); i++) {
			std::getline(std::cin, resp[i]);
		}

		int flag = 0;//�������ӵĸ���
		int count = 0;//��Ҫʹ�����ӵĸ���
		for (int i = 0; i < resp.size(); i++) {
			if (std::string::npos != (resp[i].find("c", 0))) {
				flag += 1;
			}
			if (std::string::npos != (resp[i].find("d", 0))) {
				flag -= 1;
			}
			count = flag > count ? flag : count;
		}

		std::cout << count << std::endl;
	}

	return 0;
}