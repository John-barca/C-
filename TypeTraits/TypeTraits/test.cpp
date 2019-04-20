#include <iostream>
#include <memory>
using namespace std;

//����ģ���ػ�

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

//��ģ���ػ�
//ȫ�ػ�
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

//ƫ�ػ�


//������ģ��
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

//�����ػ�����ģ���������еĲ��ֲ����ػ�
//���ڶ��������ػ�Ϊchar
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

//��������һ������
//���ģ��������и���һ��������������Ƴ�����һ���ػ��汾
//�����ػ�Ϊָ������
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
////�����ػ�Ϊ��������
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
//	Date<double, int> d1; //���û�����ģ��
//	Date<char, char> d2; //���еڶ�������Ϊchar��ģ��
//	Date<int*, char*> d3; //���ò�������Ϊָ�����ģ��
//	Date<int&, char&> d4(1,'a'); //���ò�������Ϊ���õ���ģ��
//	system("pause");
//	return 0;
//}

//��ģ���ػ�Ӧ�ã�������ȡ

//ǳ�������ֽ��򿽱�
//�Զ�������ǳ�������������
//template<class T>
//void Copy(T* dst, const T* src, size_t size)
//{
//	memcpy(dst, src, sizeof(T)*size);
//}


//�Զ�������Ӧ��ʹ�ø�ֵ
//ѭ����ֵ����Ч�ʽϵ�
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

struct TrueType//��������
{
	static bool Get()
	{
		return true;
	}
};

struct FalseType//�Զ�������
{
	static bool Get()
	{
		return false;
	}
};
//������ȡ:�Զ�������
template<class T>
struct TypeTraits
{
	typedef FalseType IsPODType;
};
//������ȡ����������
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
