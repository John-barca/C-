#include <iostream>

int main() {
	int num1, num2;
	while (std::cin >> num1 >> num2) {
		int result = 0;
		while (num1 != 0) {
			result = num1 ^ num2;
			num1 = (num1 & num2) << 1;
			num2 = result;
		}
		std::cout << num2 << std::endl;
	}
	return 0;
}