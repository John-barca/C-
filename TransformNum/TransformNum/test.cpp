#include <iostream>
#include <string>
using namespace std;

int main()
{
	int M, N;
	cin >> M >> N;//����ʮ������M��N����
	string output;//ת���ɹ��������ַ���
	string Srcstr = "0123456789ABCDEF";

	if (N < 2 || N > 16)
	{
		return 0;
	}

	if (M == 0)
	{
		output = "0";
	}

	int flag = 0;//��Ǹ����Ƿ�Ϊ����
	if (M < 0)
	{
		flag = 1;
		M = M * (-1);
	}

	while (M)
	{
		output = Srcstr[M % N] + output;
		M = M / N;
	}

	if (flag == 1)//����λ�ò��븺��
	{
		output.insert(output.begin(), '-');
	}

	cout << output << endl;
	return 0;
}