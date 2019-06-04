#include <iostream>
#include <string>
using namespace std;
#if 0
int main() {
	string str;
	int count = 1;//记录字符串个数
	getline(cin,str);
	auto sit = str.begin();//指向字符串首元素
	for (sit = str.begin(); sit != str.end(); sit++) {
		if (*sit == ' ') {
			*sit = '\n';
			count++;
		}
	}
	cout << count << endl;
	cout << str << endl;
	system("pause");
	return 0;
}
#endif


#if 0
int main() {
	string str = "a\nb\n";
	cout << str << endl;
	system("pause");
	return 0;
}
#endif



int NeedStep(int N, int M) {
	if (N > M) {
		return -1;
	}
	if (N == M) {
		return 0;
	}
	int count = 0;//记录到达目标位置所需要的次数
	for (int i = 2; i < N; i++) {
		if (N % i == 0) {
			count++;
			if ((NeedStep(N + N / i, M)) != -1) {
				count = count + NeedStep(N + N / i, M);
				return count;
			}
			else {
				count--;
			}
		}
	}
	return -1;
}

int main() {
	int N;//当前位置
	int M;//目标位置
	cin >> N >> M;

	cout << NeedStep(N, M) << endl;

	system("pause");
	return 0;
}