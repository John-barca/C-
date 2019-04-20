#include <iostream>
#include <memory>
using namespace std;

//函数模板特化

//template<class T>
//bool IsEqual(T& left, T& right)
//{
//	return left == right;
//}
//template<>
//bool IsEqual<char*>(char*& left, char*& right)
//{
//	if (strcmp(left, right) > 0)
//		return true;
//
//	return false;
//}

//void Test()
//{
//	char* p1 = (char*)"hello";
//	char* p2 = (char*)"world";
//	if (IsEqual(p1, p2))
//		cout << p1 << endl;
//	else
//		cout << p2 << endl;
//}
//
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}

//类模板特化
//全特化
//template<class T1,class T2>
//class Date
//{
//public:
//	Date()
//	{
//		cout << "Date<T1,T2>" << endl;
//	}
//private:
//	T1 _day1;
//	T2 _day2;
//};
//
//template<>
//class Date<int, char>
//{
//public:
//	Date()
//	{
//		cout << "Date<int,char>" << endl;
//	}
//private:
//	int _day1;
//	char _day2;
//};
//
//void Test()
//{
//	Date<int,int> d1;
//	Date<int, char> d2;
//}
//
//int main()
//{
//	Test();
//	system("pause");
//	return 0;
//}

//偏特化


//基础类模板
//template <class T1,class T2>
//class Date
//{
//public:
//	Date()
//	{
//		cout << "Date<T1,T2>" << endl;
//	}
//private:
//	T1 _d1;
//	T2 _d2;
//};

//部分特化：将模板参数类表中的部分参数特化
//将第二个参数特化为char
//template<class T1>
//class Date<T1, char>
//{
//public:
//	Date()
//	{
//		cout << "Date<T1,char>" << endl;
//	}
//private:
//	T1 _d1;
//	char _d2;
//};

//参数更进一步限制
//针对模板参数进行更进一步条件限制所设计出来的一个特化版本
//参数特化为指针类型
//template<class T1,class T2>
//class Date<T1*, T2*>
//{
//public:
//	Date()
//	{
//		cout << "Date<T1*,T2*>" << endl;
//	}
//private:
//	T1 _d1;
//	T2 _d2;
//};
//
////参数特化为引用类型
//template<class T1,class T2>
//class Date<T1&, T2&>
//{
//public:
//	Date(const T1& d1,const T2& d2)
//		:_d1(d1)
//		,_d2(d2)
//	{
//		cout << "Date<T1&,T2&>" << endl;
//	}
//private:
//	const T1& _d1;
//	const T2& _d2;
//};

//int main()
//{
//	Date<double, int> d1; //调用基础类模板
//	Date<char, char> d2; //调研第二个参数为char的模板
//	Date<int*, char*> d3; //调用参数类型为指针的类模板
//	Date<int&, char&> d4(1,'a'); //调用参数类型为引用的类模板
//	system("pause");
//	return 0;
//}

//类模板特化应用：类型萃取

//浅拷贝，字节序拷贝
//自定义类型浅拷贝会出现问题
//template<class T>
//void Copy(T* dst, const T* src, size_t size)
//{
//	memcpy(dst, src, sizeof(T)*size);
//}


//自定义类型应当使用赋值
//循环赋值，但效率较低
//template<class T>
//void Copy(T* dst, const T* src, size_t size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		dst[i] = src[i];
//	}
//}
//
//
//int main()
//{
//	string arr1[] = { "11","22","33" };
//	string arr2[3];
//	Copy(arr2, arr1, 3);
//	system("pause");
//	return 0;
//}

struct TrueType//内置类型
{
	static bool Get()
	{
		return true;
	}
};

struct FalseType//自定义类型
{
	static bool Get()
	{
		return false;
	}
};
//类型萃取:自定义类型
template<class T>
struct TypeTraits
{
	typedef FalseType IsPODType;
};
//类型萃取：内置类型
template<>
struct TypeTraits<char>
{
	typedef TrueType IsPODType;
};
template<>
struct TypeTraits<int>
{
	typedef TrueType IsPODType;
};
template<>
struct TypeTraits<long>
{
	typedef TrueType IsPODType;
};
template<>
struct TypeTraits<short>
{
	typedef TrueType IsPODType;
};
template<>
struct TypeTraits<double>
{
	typedef TrueType IsPODType;
};
template<>
struct TypeTraits<float>
{
	typedef TrueType IsPODType;
};
template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	if (TypeTraits<T>::IsPODType::Get())
	{
		memcpy(dst, src, sizeof(T) * size);
	}
	else
	{
		for (size_t i = 0; i < size; i++)
		{
			dst[i] = src[i];
		}
	}
}

int main()
{
	int a1[] = { 1,2,3,4 };
	int a2[4];
	Copy(a2, a1, 4);

	string arr1[] = { "11111","33333" };
	string arr2[2];
	Copy(arr2, arr1, 2);

	return 0;
}
