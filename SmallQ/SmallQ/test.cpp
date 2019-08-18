//#include <iostream>
//#include <string>
//
//int main() {
//	std::string str;
//	std::string result = "";
//	while (std::getline(std::cin, str)) {
//		size_t begin, end;
//		if (str.find('[', 0) != std::string::npos) {
//			begin = str.find('[', 0);
//		}
//		else {
//			result = str;
//			std::cout << result << std::endl;
//			return 0;
//		}
//
//		if (str.rfind(']', str.size() - 1) != std::string::npos) {
//			end = str.rfind(']', str.size() - 1);
//		}
//
//		int i;
//		for (i = 0; i < begin; i++) {
//			result += str[i];
//		}
//
//		int count; // 记录字符串里的数字
//		std::string num = "";
//		if (i == begin) {
//			while (str[i] != '|') {
//				if (str[i] >= '0' && str[i] <= '9') {
//					num += str[i];
//				}
//				i++;
//			}
//		}
//	}
//
//	return 0;
//}




//#include <iostream>
//#include <vector>
//
//int Calculate(std::vector<int>& Horse, int i) {
//	int left = 0, right = 0;
//	int flag1 = Horse[i];
//	for (int j = i + 1; j < Horse.size(); j++) {
//		if (Horse[j] < flag1 && j - 1 == i) {
//			right++;
//			flag1 = Horse[j];
//		}
//		else if (Horse[j] > flag1 && flag1 <= Horse[i]) {
//			right++;
//			flag1 = Horse[j];
//		}
//		else if (Horse[j] > flag1 && flag1 > Horse[i]) {
//			right++;
//			flag1 = Horse[j];
//		}
//	}
//
//	int flag = Horse[i];
//	for (int z = i - 1; z >= 0; z--) {
//		
//		if (Horse[z] < flag && z + 1 == i) {
//			left++;
//			flag = Horse[z];
//		}
//		else if (Horse[z] > flag && flag <= Horse[i]) {
//			left++;
//			flag = Horse[z];
//		}
//		else if (Horse[z] > flag && flag > Horse[i]) {
//			left++;
//			flag = Horse[z];
//		}
//	}
//
//	return left + right + 1;
//}
//
//int main() {
//	int n; // 楼的栋数
//	while (std::cin >> n) {
//		std::vector<int> Horse;
//		Horse.resize(n);
//		for (int i = 0; i < n; i++) {
//			std::cin >> Horse[i];
//		}
//
//		std::vector<int> result;
//		result.resize(n);
//		
//		for (int i = 0; i < Horse.size(); i++) {
//			int count = Calculate(Horse, i);
//			result[i] = count;
//		}
//
//		auto it = result.begin();
//		while (it != result.end() - 1) {
//			std::cout << *it << " ";
//			it++;
//		}
//		std::cout << *it << std::endl;
//	}
//
//	return 0;
//}


#include <iostream>
#include <vector>

int main() {
	int n, L; // n表示道具的个数, L表示河流的长度
	while (std::cin >> n >> L) {
		std::vector<int> sodier;
		sodier.resize(2);
		std::vector<std::vector<int>> num;
		num.resize(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2; j++) {
				std::cin >> sodier[j];
			}
			num[i] = sodier;
		}

		int begin = n;
		int end = 0; 
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (num[i][1] > end && num[i][1] <= n) {
				end = num[i][1];
				if (num[i][0] < begin) {
					begin = num[i][0];
				}
				count++;
			}
			else if (num[i][0] < begin) {
				begin = num[i][0];
				if (num[i][1] > end && num[i][1] <= n) {
					end = num[i][1];
				}
				count++;
			}
		}

		if (end == n && begin == 0) {
			std::cout << count << std::endl;
		}
		else {
			std::cout << "-1" << std::endl;
		}

	}

	return 0;
}