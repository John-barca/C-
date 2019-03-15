#include <iostream>
using namespace std;
//
//class Date
//{
//	friend ostream& operator<<(ostream& outs, Date& d);
//public:
//	Date(int year=1900,int month=1,int day=1)
//		:_year(year)
//		,_month(month)
//		,_day(day)
//	{}
//
//	/*void operator<<(ostream& outs)
//	{
//		outs << _year << "-" << _month << "-" << _day << endl;
//	}*/
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//
//ostream& operator<<(ostream& outs, Date& d)
//{
//	outs << d._year << "-" << d._month << "-" << d._day << endl;
//	return outs;
//}
//
//int main()
//{
//	Date d1;
//	//operator<<(cout, d1);
//	cout << d1 << d1 << d1 << d1;
//	//d1.operator<<(cout);
//	//d1 << cout;
//	system("pause");
//	return 0;
// }

class Solution {
public:
	class Sum {
	public:
		Sum()
		{
			_sum += _i;
			++_i;
		}
	};

	Solution()
	{}
	int Sum_Solution(int n)
	{
		_sum = 0;
		_i = 1;
		Sum arr[10];
		return _sum;
	}

private:
	static int _sum;
	static int _i;
};

int Solution::_sum = 0;
int Solution::_i = 1;

int main()
{
	Solution s;
	cout << s.Sum_Solution << endl;
}