#include <iostream>
#include <cmath>

int main() {
	int num;
	while (std::cin >> num) {
		std::cout << num << " = ";
		//int count = 0;
		int tmp = num;
		for (int i = 2; i <= sqrt(tmp); i++) {
			while (num != i) {
				if (num % i == 0) {
					num /= i;
					/*if (count != 0) {
						std::cout << " * ";
					}*/
					std::cout << i << " * ";
					//std::cout << count;
					//count++;
				}
				else {
					break;
				}
			}
		}
		std::cout << num;
		std::cout << std::endl;
	}

	return 0;
}