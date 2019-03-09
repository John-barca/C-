#include <iostream>
using namespace std;


class Date
{
public:

	Date(int year = 1900, int month = 1, int day = 1)
	{
		this->_year = year;
		this->_month = month;
		this->_day = day;
	}
	~Date() {
		cout << "~Date()" << endl;
	}
	int GetMonthDay(int year, int month)
	{
		int array[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		if (month == 2)
		{
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
			{
				return array[month] + 1;
			}
			else {
				return array[month];
			}
		}
		return array[month];
	}

	Date(const Date &d)
	{
		cout << "Date(const Date &d)" << endl;
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._month;
		}
		return *this;
	}

	Date& operator+=(int days)
	{
		if (days < 0)
		{
			return *this -= -days;
		}
		_day += days;
		while (_day > GetMonthDay(_year, _month))
		{
			++_month;
			if (_month == 13)
			{
				_month = 1;
				++_year;
			}
		}
		return *this;
	}

	Date& operator-=(int days)
	{
		if (days < 0)
		{
			return *this += -days;
		}
		_day -= days;
		while (_day <= 0)
		{
			--_month;
			if (_month == 0)
			{
				_month = 12;
				--_year;
			}
			_day += GetMonthDay(_year, _month);
		}
		return *this;
	}

	Date operator+(int days)
	{
		return (*this += days);

	}

	Date operator-(int days)
	{
		return (*this -= days);
	}

	int operator-(const Date& d)
	{
		int count = 0;
		int flag = 1;
		Date ret = *this;
		if (ret < d)
		{
			while (ret < d)
			{
				flag = -1;
				++ret;
				++count;
			}
		}
		else
		{
			while (ret > d)
			{
				--ret;
				++count;
			}
		}
		return (flag * count);


	}

	Date& operator++()//前置
	{
		return (*this += 1);
	}
	Date operator++(int)//后置
	{
		Date ret = *this;
		*this += 1;
		return ret;
	}
	Date& operator--()
	{
		return (*this -= 1);
	}
	Date operator--(int) {
		Date ret = *this;
		*this -= 1;
		return ret;
	}
	bool operator>(const Date& d)const
	{
		if ((_year > d._year) || (_year == d._year&&_month > d._month) || (_year == d._year&&_month == d._month&&_day > d._day))
		{
			return true;
		}
		else {
			return false;
		}
	}
	bool operator==(const Date& d)const
	{
		if ((_year == d._year) && (_month == d._month) && (_day == d._day))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator>=(const Date& d)const
	{
		return ((*this > d) || (*this == d));
	}
	bool operator<(const Date& d)const
	{
		return !(*this >= d);
	}
	bool operator<=(const Date& d)const
	{
		return (*this < d) || (*this == d);
	}
	bool operator!=(const Date& d)const
	{
		return !(*this == d);
	}


	void Display() {
		std::cout << _year << "年" << _month << "月" << _day << "日" << endl;
	}

	void SetDate(int year, int month, int day)
	{
		if ((year < 1900) || (month < 1) || (month > 12) || (day < 1) || (day > GetMonthDay(year, month)))
		{
			cout << "非法日期，输入错误" << endl;
		}
		_year = year;
		_month = month;
		_day = day;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2018, 5, 6);
	Date d2(2004, 5, 4);
	Date d3;
	d3 = d2 + 50;
	Date d4;
	d4 = d2 - 3;
	cout << "over" << endl;
	return 0;
}