#include <iostream>
using namespace std;

int main() {
	int Num = 0;
	cin >> Num;
	int tmp = Num; //�м�ֵ
	int count = 0; //��¼�ö���������1�ĸ���
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