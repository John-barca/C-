#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <string>
using namespace std;

int The_root_num(int n) {
	int result = 0;
	if (n < 10) {
		return n;
	}
	while (n > 0) {
		result += n % 10;
		n /= 10;
	}
	if (result >= 10) {
		result = The_root_num(result);
	}
	return result;
}

int main() {
	string num;
	while (cin >> num) {
		int result = 0;
		auto it = num.begin();
		while (it != num.end()) {
			result += (*it - '0');
			it++;
		}
		result = The_root_num(result);
		cout << result << endl;
	}
	return 0;
}
//
//int main() {
//	int num[4];
//	int result = 0;
//	char c;
//	int i = 0;
//	while ((c = getchar()) != '\n' && c != EOF) {
//		result += (c - '0');
//	}
//	
//	while (result > 9) {
//		memset(num, 0, sizeof(num));
//
//		for (i = 0; i < sizeof(num) / sizeof(num[0]); i++) {
//			num[i] = result & 10;
//			result /= 10;
//			result += num[i];
//		}
//	}
//
//	printf("%d\n", result);
//	system("pause");
//	return 0;
//}
//char num[10001];
//
//int main() {
//	int result = 0;
//	int i = 0;
//	while (scanf("%s", num) != EOF) {
//
//	}
//
//
//	system("pause");
//	return 0;
//}