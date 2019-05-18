#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
//密码安全情况得分

void Safelevel(string pPasswordStr)
{
	int count = 0;
	int len = pPasswordStr.size();
	if (len <= 4)
	{
		count += 5;
	}
	else if ((len > 4) && (len < 8))
	{
		count += 10;
	}
	else if (len > 8 || len == 8)
	{
		count += 25;
	}
	string::iterator it = pPasswordStr.begin();
	int num = 0;//记录字母的个数
	int flagBig = 0;//大写字母个数
	int flagSmall = 0; //小写字母个数
	int flagNum = 0; //记录数字的个数
	int flagChar = 0; //记录字符的个数
	while (it != pPasswordStr.end())
	{
		//判断大小写字母
		if ((*it >= 'A') && (*it <= 'Z')) 
		{
			flagBig++;
		}
		if ((*it >= 'a') && (*it <= 'z'))
		{
			flagSmall++;
		}
		//数字个数
		if ((*it > '1') && (*it < '9'))
		{
			flagNum++;
		}

		//字符个数
		if (((*it >= '!') && (*it <= '/')) || ((*it >= ':') && (*it <= '@')) || ((*it >= '[') && (*it <= '`')) || ((*it >= '{') && (*it <= '~')))
		{
			flagChar++;
		}
		it++;
	}
	//字母
	num = flagBig + flagSmall;
	if ((flagBig != 0) && (flagSmall != 0))
	{
		count += 20;
	}
	if (((flagBig != 0) && (flagSmall == 0)) || ((flagBig == 0) && (flagSmall != 0)))
	{
		count += 10;
	}

	//数字
	if (flagNum == 1)
	{
		count += 10;
	}
	else if (flagNum > 1)
	{
		count += 20;
	}

	//字符
	if (flagChar == 1)
	{
		count += 10;
	}
	else if (flagChar > 1)
	{
		count += 25;
	}

	if (flagBig && flagSmall && flagNum && flagChar)
	{
		count += 5;
	}
	else if (flagChar && flagNum && num)
	{
		count += 3;
	}
	else if (num && flagNum)
	{
		count += 2;
	}


	if (count >= 90)
	{
		cout << "VERY_SECURE" << endl;
	}
	else if ((count < 90) && (count >= 80))
	{
		cout << "SECURE" << endl;
	}
	else if ((count < 80) && (count >= 70))
	{
		cout << "VERY_STRONG" << endl;
	}
	else if ((count < 70) && (count >= 60))
	{
		cout << "STRONG" << endl;
	}
	else if ((count < 60) && (count >= 50))
	{
		cout << "AVERAGE" << endl;
	}
	else if ((count < 50) && (count >= 25))
	{
		cout << "WEAK" << endl;
	}
	else {
		cout << "VERY_WEAK" << endl;
	}
}

int main()
{
	string pPasswordStr;
	while (cin >> pPasswordStr)
	{
		Safelevel(pPasswordStr);
	}
	system("pause");
	return 0;
}