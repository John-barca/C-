#include <iostream>
#include <stdlib.h>
#include <thread>
#include <mutex>
using namespace std;

//RAII思想设计的SmartPtr类
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
////智能指针原理：
////RAII：利用对象生命周期来控制程序资源
////重载operator*和operator->,具有像指针一样的行为
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

//auto_ptr：C++98
//C++库中智能指针在memory头文件里
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
//	//当对象拷贝或者赋值后，前面的对象悬空
//	sp->_year = 2019;
//	return 0;
//}

//auto_ptr实现原理：管理权转移
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
//	//一旦发生拷贝，就将sp中资源转移到当前对象中
//	//然后另sp与其所管理资源断开联系
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

	//一旦发生拷贝，就将sp中资源转移到当前对象中
	//然后另sp与其所管理资源断开联系
	//解决一块空间被多个对象使用而造成程序崩溃问题
	AutoPtr(AutoPtr<T>& sp)
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}

	AutoPtr<T>& operator=(AutoPtr<T>& sp)
	{
		//检测是否为自己给自己赋值
		if (this != &sp)
		{
			//释放当前对象中资源
			if (_ptr)
			{
				delete _ptr;
			}

			//将sp中资源转移到当前对象中
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
//	//发生拷贝，把sp对象的指针赋空，导致sp对象悬空
//	//sp对象访问资源时就会出现问题
//	AutoPtr<Date> copysp(sp);
//	
//	copysp->_year = 2010;
//	sp->_year = 2019;//空指针解引用
//	return 0;
//}

//int main()
//{
//	unique_ptr<Date> up(new Date);
//
//	//unique_ptr设计思路 => 防拷贝，封掉拷贝构造函数
//	unique_ptr<Date> copy(up);//显示它是已删除的函数
//	return 0;
//}

//模拟实现unique_ptr
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
//	//C++防拷贝方式，之生命不实现+声明或私有
//	UniquePtr(UniquePtr<T> const &);
//	UniquePtr& operator=(UniquePtr<T> const &);
//
//	//C++11防拷贝的方式:delete
//	UniquePtr(UniquePtr<T> const &) = delete;
//	UniquePtr& operator=(UniquePtr<T> const &) = delete;
//private:
//	T* _ptr;
//};

//shared_ptr:靠谱且支持拷贝
//int main()
//{
//	//shared_ptr 通过引用计数支持智能指针对象的拷贝
//	shared_ptr<Date> sp(new Date);
//	shared_ptr<Date> spcopy(sp);
//
//	cout << "ref count:" << sp.use_count() << endl;//use_count: 2
//	cout << "ref count:" << spcopy.use_count() << endl;//use_count: 2
//	system("pause");
//	return 0;
//}

//shared_ptr原理：通过引用计数的方式实现多个shared_ptr对象之间共享资源
//1.给每个资源维护一份计数，用来记录该份资源被几个资源共享
//2.在对对象销毁时(析构函数调用),对象的引用计数减1
//3.如果引用计数是0，就说明自己是最后一个使用该资源的对象，必须释放资源
//4.如果不是0，那么说明除了自己还有其他对象使用该份资源
//不能释放该资源，否则其它对象就成了野指针

//模拟实现一份SharePtr
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
			//释放管理的旧资源
			Release();

			//共享管理新对象的资源，并增加引用计数
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
		//加锁或者使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool flag = false;
		//引用计数减1，如果减到0，则释放资源
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
	int* _pRefCount; //引用计数
	T* _ptr;		//指向管理资源的指针
	mutex* _pMutex;	//互斥锁
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