#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
//���밲ȫ����÷�

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
	int num = 0;//��¼��ĸ�ĸ���
	int flagBig = 0;//��д��ĸ����
	int flagSmall = 0; //Сд��ĸ����
	int flagNum = 0; //��¼���ֵĸ���
	int flagChar = 0; //��¼�ַ��ĸ���
	while (it != pPasswordStr.end())
	{
		//�жϴ�Сд��ĸ
		if ((*it >= 'A') && (*it <= 'Z')) 
		{
			flagBig++;
		}
		if ((*it >= 'a') && (*it <= 'z'))
		{
			flagSmall++;
		}
		//���ָ���
		if ((*it > '1') && (*it < '9'))
		{
			flagNum++;
		}

		//�ַ�����
		if (((*it >= '!') && (*it <= '/')) || ((*it >= ':') && (*it <= '@')) || ((*it >= '[') && (*it <= '`')) || ((*it >= '{') && (*it <= '~')))
		{
			flagChar++;
		}
		it++;
	}
	//��ĸ
	num = flagBig + flagSmall;
	if ((flagBig != 0) && (flagSmall != 0))
	{
		count += 20;
	}
	if (((flagBig != 0) && (flagSmall == 0)) || ((flagBig == 0) && (flagSmall != 0)))
	{
		count += 10;
	}

	//����
	if (flagNum == 1)
	{
		count += 10;
	}
	else if (flagNum > 1)
	{
		count += 20;
	}

	//�ַ�
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