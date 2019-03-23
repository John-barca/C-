#include <iostream>
#include <string>
using namespace std;


//class Solution {
//public:
//	string addStrings(string num1, string num2) {
//		size_t i = 0, j = 0;
//		int ret1 = 0, ret2 = 0;
//		int sum = 0;
//		while (i < num1.size())
//		{
//			ret1 *= 10;
//			ret1 = ret1 + num1[i] - '0';
//			++i;
//		}
//		sum = ret1;
//		while (j < num2.size())
//		{
//			ret2 *= 10;
//			ret2 = ret2 + num2[j] - '0';
//			++j;
//		}
//		sum += ret2;
//		string s;
//		s = sum + '0';
//		return s;
//		
//	}
//};

class Solution {
public:
	string addStrings(string num1, string num2) {
		int len1 = num1.size() - 1;
		int len2 = num2.size() - 1;
		int sum = 0;
		int step = 0;
		string cur = "";
		while (len1 >= 0 || len2 >= 0)
		{
			sum = 0;
			sum += step;
			if (len1 >= 0)
			{
				sum += num1[len1] - '0';
			}
			if (len2 >= 0)
			{
				sum += num2[len2] - '0';
			}
			if (sum > 9)
			{
				step = 1;
			}
			else
			{
				step = 0;
			}
			cur.insert(0, 1, sum + '0');


			len1--;
			len2--;
		}
		if (step == 1)
		{
			cur.insert(0, 1, '1');
		}
		return cur;
	}
};



int main()
{
	Solution s;
	string num1;
	string num2;
	while (cin >> num1 >> num2)
	{
		cout << s.addStrings(num1, num2);
	}
	return 0;
}