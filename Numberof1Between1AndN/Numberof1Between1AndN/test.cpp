//整数1到n中1出现的次数
#include <iostream>
using namespace std;

class Solution {
public:
	int Numberof1(int n)
	{
		int number = 0;
		while (n)
		{
			if (n % 10 == 1)
			{
				number++;
			}
			n = n / 10;
		}
		return number;
	}

	int NumberOf1Between1AndN_Solution(int n)
	{
		int count = 0;
		for (int i = 1; i <= n; i++)
		{
			count += Numberof1(i);
		}
		return count;
	}
};