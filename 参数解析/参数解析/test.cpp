#include <iostream>
#include <string>
using namespace std;
#if 0
int main() {
	string str;
	int count = 1;//��¼�ַ�������
	getline(cin,str);
	auto sit = str.begin();//ָ���ַ�����Ԫ��
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
	int count = 0;//��¼����Ŀ��λ������Ҫ�Ĵ���
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
	int N;//��ǰλ��
	int M;//Ŀ��λ��
	cin >> N >> M;

	cout << NeedStep(N, M) << endl;

	system("pause");
	return 0;
}