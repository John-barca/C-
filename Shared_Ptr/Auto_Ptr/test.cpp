#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
using namespace std;

//RAII˼����Ƶ�SmartPtr��
//template <class T>
//class SmartPtr
//{
//public:
//	SmartPtr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//
//	~SmartPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//		}
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//private:
//	T* _ptr;
//};
//
////����ָ��ԭ��
////RAII�����ö����������������Ƴ�����Դ
////����operator*��operator->,������ָ��һ������Ϊ
//
//struct Date {
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	SmartPtr<int> sp(new int);
//	*sp = 10;
//	cout << *sp << endl;
//
//	SmartPtr<Date> array(new Date);
//	array.operator->()->_year = 2018;
//	array->_month = 1;
//	array->_day = 1;
//	return 0;
//}

//auto_ptr��C++98
//C++��������ָ����memoryͷ�ļ���
#include<memory>
//
class Date {
public:
	Date(){
		cout << "Date()" << endl;
	}
	~Date()
	{
		cout << "~Date" << endl;
	}

	int _year;
	int _month;
	int _day;
};
//
//int main()
//{
//	auto_ptr<Date> sp(new Date);
//	auto_ptr<Date> copysp(sp);
//
//	//�����󿽱����߸�ֵ��ǰ��Ķ�������
//	sp->_year = 2019;
//	return 0;
//}

//auto_ptrʵ��ԭ������Ȩת��
//template <class T>
//class AutoPtr
//{
//public:
//	AutoPtr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//
//	~AutoPtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//		}
//	}
//
//	//һ�������������ͽ�sp����Դת�Ƶ���ǰ������
//	//Ȼ����sp������������Դ�Ͽ���ϵ
//	AutoPtr(AutoPtr<T>& sp)
//		:_ptr(sp._ptr)
//	{
//		sp._ptr = nullptr;
//	}
//
//	AutoPtr<T>& operator=
//private:
//	T* _ptr;
//};

template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = nullptr)
		:_ptr(ptr)
	{}

	~AutoPtr()
	{
		if (_ptr)
		{
			delete _ptr;
		}
	}

	//һ�������������ͽ�sp����Դת�Ƶ���ǰ������
	//Ȼ����sp������������Դ�Ͽ���ϵ
	//���һ��ռ䱻�������ʹ�ö���ɳ����������
	AutoPtr(AutoPtr<T>& sp)
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& sp)
	{
		//����Ƿ�Ϊ�Լ����Լ���ֵ
		if (this != &sp)
		{
			//�ͷŵ�ǰ��������Դ
			if (_ptr)
			{
				delete _ptr;
			}

			//��sp����Դת�Ƶ���ǰ������
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
		return *this;
	}

	T& operator*()
	{
		return *this;
	}

	T* operator->()
	{
		return _ptr;
	}
private:
	T* _ptr;
};

//int main()
//{
//	AutoPtr<Date> sp(new Date);
//	
//	//������������sp�����ָ�븳�գ�����sp��������
//	//sp���������Դʱ�ͻ��������
//	AutoPtr<Date> copysp(sp);
//	
//	copysp->_year = 2010;
//	sp->_year = 2019;//��ָ�������
//	return 0;
//}

//int main()
//{
//	unique_ptr<Date> up(new Date);
//
//	//unique_ptr���˼· => ������������������캯��
//	unique_ptr<Date> copy(up);//��ʾ������ɾ���ĺ���
//	return 0;
//}

//ģ��ʵ��unique_ptr
//template<class T>
//class UniquePtr
//{
//public:
//	UniquePtr(T* ptr = nullptr)
//		:_ptr(ptr)
//	{}
//
//	~UniquePtr()
//	{
//		if (_ptr)
//		{
//			delete _ptr;
//		}
//	}
//
//	T& operator*()
//	{
//		return *_ptr;
//	}
//
//	T* operator->()
//	{
//		return _ptr;
//	}
//private:
//	//C++��������ʽ��֮������ʵ��+������˽��
//	UniquePtr(UniquePtr<T> const &);
//	UniquePtr& operator=(UniquePtr<T> const &);
//
//	//C++11�������ķ�ʽ:delete
//	UniquePtr(UniquePtr<T> const &) = delete;
//	UniquePtr& operator=(UniquePtr<T> const &) = delete;
//private:
//	T* _ptr;
//};

//shared_ptr:������֧�ֿ���
//int main()
//{
//	//shared_ptr ͨ�����ü���֧������ָ�����Ŀ���
//	shared_ptr<Date> sp(new Date);
//	shared_ptr<Date> spcopy(sp);
//
//	cout << "ref count:" << sp.use_count() << endl;//use_count: 2
//	cout << "ref count:" << spcopy.use_count() << endl;//use_count: 2
//	system("pause");
//	return 0;
//}

//shared_ptrԭ��ͨ�����ü����ķ�ʽʵ�ֶ��shared_ptr����֮�乲����Դ
//1.��ÿ����Դά��һ�ݼ�����������¼�÷���Դ��������Դ����
//2.�ڶԶ�������ʱ(������������),��������ü�����1
//3.������ü�����0����˵���Լ������һ��ʹ�ø���Դ�Ķ��󣬱����ͷ���Դ
//4.�������0����ô˵�������Լ�������������ʹ�ø÷���Դ
//�����ͷŸ���Դ��������������ͳ���Ұָ��

//ģ��ʵ��һ��SharePtr
template<class T>
class SharePtr
{
public:
	SharePtr(T* ptr = nullptr)
		:_pRefCount(new int(1))
		,_ptr(ptr)
		,_pMutex(new mutex)
	{}

	~SharePtr()
	{
		Release();
	}

	SharePtr(const SharePtr<T>& sp)
		:_pRefCount(sp._pRefCount)
		,_ptr(sp._ptr)
		,_pMutex(sp._pMutex)
	{
		AddRefCount();
	}

	//sp1 = sp2
	SharePtr<T>& operator=(const SharePtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			//�ͷŹ���ľ���Դ
			Release();

			//��������¶������Դ�����������ü���
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;

			AddRefCount();
		}
		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	int UseCount()
	{
		return *_pRefCount;
	}

	T* Get()
	{
		return _ptr;
	}

	void AddRefCount()
	{
		//��������ʹ�ü�1��ԭ�Ӳ���
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool flag = false;
		//���ü�����1���������0�����ͷ���Դ
		_pMutex->lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			flag = true;
		}
		_pMutex->unlock();

		if (flag == true)
		{
			delete _pMutex;
		}
	}
private:
	int* _pRefCount; //���ü���
	T* _ptr;		//ָ�������Դ��ָ��
	mutex* _pMutex;	//������
};

int main()
{
	SharePtr<int> sp1(new int(10));
	SharePtr<int> sp2(sp1);
	*sp2 = 20;

	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;

	SharePtr<int> sp3(new int(10));
	sp2 = sp3;
	cout << "sp1:" << sp1.UseCount() << endl;
	cout << "sp2:" << sp2.UseCount() << endl;
	cout << "sp3:" << sp3.UseCount() << endl;

	sp1 = sp3;
	cout << "sp1:" << sp1.UseCount() << endl;
	cout << "sp2:" << sp2.UseCount() << endl;
	cout << "sp3:" << sp3.UseCount() << endl;

	system("pause");
	return 0;
}