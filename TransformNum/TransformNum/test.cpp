#include <iostream>
#include <string>
using namespace std;

int main()
{
	int M, N;
	cin >> M >> N;//输入十进制数M，N进制
	string output;//转换成功后的输出字符串
	string Srcstr = "0123456789ABCDEF";

	if (N < 2 || N > 16)
	{
		return 0;
	}

	if (M == 0)
	{
		output = "0";
	}

	int flag = 0;//标记该数是否为负数
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

	if (flag == 1)//向首位置插入负号
	{
		output.insert(output.begin(), '-');
	}

	cout << output << endl;
	return 0;
}