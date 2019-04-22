#include <iostream>
using namespace std;


//一次跳一阶或者两阶，有n级台阶，共有多少种跳法
//class Solution {
//public:
//	int jumpFloor(int number) {
//		if (number == 0)
//		{
//			return 0;
//		}
//		if (number == 1)
//		{
//			return 1;
//		}
//		if (number == 2)
//		{
//			return 2;
//		}
//		int first = 1;
//		int second = 2, third = 0;
//		for (int i = 3; i <= number; i++)
//		{
//			third = first + second;
//			first = second;
//			second = third;
//		}
//		return third;
//	}
//};

//一次可以条1级，也可以2级，也可以n级，有多少种跳法
class Solution {
public:
	int jumpFloorII(int number) {
		int count = 0;
		if (number == 0)
		{
			return 1;
		}
		for (int i = 1; i <= number; i++)
		{
			count += jumpFloorII(number - i);
		}
		return count;
	}
};