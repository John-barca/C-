#include <iostream>
using namespace std;

class Solution {
public:
	int StrToInt(string str)
	{
		if (str.empty())
		{
			return 0;
		}
		string::iterator sit = str.begin();
		int ret = 0;
		int flag = -1;
		while (sit != str.end())
		{
			ret *= 10;
			if (*sit >= '0'&&*sit <= '9')
			{
				ret += *sit - '0';//×Ö·û×ªÊý×Ö
			}
			else if (*sit == '-' || *sit == '+')
			{
				if (*sit == '-')
				{
					flag = -1;
				}
			}
			else {
				return 0;
			}
			++sit;
		}
		return ret * flag;
	}
};