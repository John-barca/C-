#include <iostream>
using namespace std;


//һ����һ�׻������ף���n��̨�ף����ж���������
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

//һ�ο�����1����Ҳ����2����Ҳ����n�����ж���������
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