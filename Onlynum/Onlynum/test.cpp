//#include <iostream>
//using namespace std;
//
//int main() {
//	int num;//���������
//	while (cin >> num) {
//		int onlynum1 = 2;
//		int onlynum2 = 2;
//		int min = 0;//��С��ֵ
//		int count = 0;//��¼���뺯���Ĵ���
//		/*for (int i = 2; i < num; i++) {
//			for (int j = 2; j < num; j++) {
//				if (i + j == num) {
//					if ((i % 2 == 1 && i / 2 != 1) || (i == 2)) {
//						if ((j % 2 == 1 && j / 2 != 1) || (j == 2)) {
//							int tmp = i > j ? (i - j) : (j - i);
//							if (tmp < min) {
//								min = tmp;
//								onlynum1 = i;
//								onlynum2 = j;
//							}
//						}
//					}
//				}
//			}
//		}*/
//		for (int i = 2; i < num; i++) {
//			for (int j = 2; j < num; j++) {
//				if (((j % i != 0) && (i % j != 0)) || (i == 2 || j == 2)) {
//					if (i + j == num) {
//						int tmp = i > j ? (i - j) : (j - i);
//						if (count == 0 || tmp < min) {
//							min = tmp;
//							onlynum1 = i;
//							onlynum2 = j;
//							count++;
//						}
//					}
//				}
//			}
//
//			
//		}
//		cout << onlynum1 << endl;
//		cout << onlynum2 << endl;
//	}
//	return 0;
//}

#include <iostream>
using namespace std;

bool IsOnlynum(int num) {
	int tmp = 2;
	for (tmp = 2; tmp <= num; tmp++) {
		if (num % tmp == 0) {
			break;
		}
	}
	if (tmp < num) {
		return false;
	}
	else {
		return true;
	}
}

int main() {
	int num;
	while (cin >> num) {
		int onlynum1 = 0;
		int onlynum2 = 0;
		int i = 2;//��ʼԪ������
		int min = 0;//��¼��С��ֵ
		int count = 0;//��¼�����жϺ����Ĵ���
		for (i = 2; i < num - 2; i++) {
			int j = num - i;
			if (IsOnlynum(i) && IsOnlynum(j)) {
				int tmp = i > j ? (i - j) : (j - i);
				if (count == 0 || tmp < min) {
					min = tmp;
					onlynum1 = i;
					onlynum2 = j;
					count++;
				}
			}
		}
		cout << onlynum1 << endl;
		cout << onlynum2 << endl;

	}

	return 0;
}