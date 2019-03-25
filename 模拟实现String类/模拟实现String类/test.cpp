#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <assert.h>
using namespace std;

class String {
	friend ostream& operator<<(ostream& cout, const String& s);
public:
	typedef char* Iterator;
public:
	String(const char* str="")
	{
		if (str == nullptr)
		{
			str = "";
		}
		_size = strlen(str);
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		:_str(new char[s._capacity + 1])
		,_size(s._size)
		,_capacity(s._capacity)
	{
		String Tmp(s._str);
		strcpy(_str, Tmp._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pstr = new char[s._capacity + 1];
			strcpy(pstr, _str);
			delete[] _str;
			_str = pstr;
			_size = s._size;
			_capacity = s._capacity;
		}
		return *this;
	}

	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_size, s._size);
		swap(_capacity, s._capacity);
	}



	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}

	void Reverse(size_t n)
	{
		if (n > _capacity)
		{
			if (_capacity == 0)
			{
				_capacity = 15;
			}
			char* newc = new char[_capacity == 0 ? 15 : _capacity * 2];
			strcpy(newc, _str);
			delete[] _str;
			_str = newc;
		}
	}

	void PushBack(const char c)
	{
		if (_size == _capacity)
		{
			Reverse(_capacity==0 ? 15 : _capacity * 2);
		}
		_str[_size++] = c;
		_str[_size] = '\0';
	}

	void Append(const char *str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			Reverse(len + _size);
		}
		strcpy(_str + _size, str);
		_size += len;
	}

	void Resize(size_t n, char c = '\0')
	{
		if (n > _capacity)
		{
			Reverse(n);
		}
		if (n > _size)
		{
			memset(_str + _size, c, n - _size);
		}
		_size = n;
		_str[_size] = '\0';
	}

	//1.检查空间是否足够 _size ==_capacity 如果已满 增容
	//2.留出pos位置,用于插入字符c 从pos开始的所有字符 向后移动一个位置：数据挪动方向从后向前依次挪动，否则会造成数据覆盖
	//3.在pos位置插入c
	//4.更新_size，_size++。更新'\0'位置，_str[_size]='\0'
	void Insert(const char c, size_t pos)//在pos位置插入字符
	{
		assert(pos <= _size);
		if (_size == _capacity)
		{
			size_t newc = (_capacity == 0 ? 15 : _capacity * 2);
			Reverse(newc);
		}
		size_t end = _size;
		while (pos < end)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos] = c;
		_str[++_size] = '\0';
	}
		
	//1.检查空间。不够增容
	//2.从pos位置开始的数据依次向后挪动len个位置
	//3.把str从pos位置开始拷贝
	//4.更新_size
	void Insert(size_t pos, const char* str)//在pos位置插入字符串
	{
		size_t len = strlen(str);
		if (_size + len >= _capacity)
		{
			Reverse(_size + len);
		}
		size_t end = _size + len;
		//从后向前搬移数据
		while (pos + len - 1 < end)
		{
			_str[end] = _str[end - len];
			--end;
		}
		//从pos位置开始拷贝str
		for (size_t i = 0; i < len; i++)
		{
			_str[i + pos] = str[i];
		}
		_size += len;
	}

	//1.pos + len>_size，相当于从pos位置开始的字符都被删除，则将'\0'放至pos处,更新_size=pos,_str[size]='\0'
	//2.pos + len <= _size,从pos+len位置开始向前挪动len个位置，更新_size-=len,从前向后挪
	void Erase(size_t pos, size_t len)
	{
		//判断位置是否合法
		assert(pos < _size);
		//pos+len>_size,pos位置后元素全部删除
		if (pos + len > _size)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			//从前向后移动
			size_t start = pos + len;
			while (start < _size)
			{
				_str[pos++] = _str[start++];
			}
			_size -= len;
			_str[_size] = '\0';
		}

	}

	Iterator begin()
	{
		return _str;
	}

	Iterator end()
	{
		return _str + _size;
	}



private:
	
	char* _str;
	size_t _size;
	size_t _capacity;
};

ostream& operator<<(ostream& _cout, String& s)
{
	for (auto& e : s)
	{
		_cout << e << "";
	}
	_cout << endl;
	return _cout;
}


int main()
{
	String s;
	s.PushBack('A');
	s.PushBack('B');
	s.PushBack('Q');
	s.Append("1456");
	s.Insert(4, "ios");
	s.Insert('c', 7);
	s.Erase(5, 2);
	s.Erase(2, 50);
	system("pause");
	return 0;
}