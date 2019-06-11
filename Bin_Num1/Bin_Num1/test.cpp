#include <iostream>
using namespace std;

int main() {
	int Num = 0;
	cin >> Num;
	int tmp = Num; //中间值
	int count = 0; //记录该二进制数中1的个数
	while (tmp) {
		tmp = tmp & 1;
		if (tmp == 1) {
			count++;
		}
		Num = Num << 1;
		tmp = Num;
	}
	cout << count << endl;
	system("pause");
	return 0;
}