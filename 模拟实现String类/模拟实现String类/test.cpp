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

	//1.���ռ��Ƿ��㹻 _size ==_capacity ������� ����
	//2.����posλ��,���ڲ����ַ�c ��pos��ʼ�������ַ� ����ƶ�һ��λ�ã�����Ų������Ӻ���ǰ����Ų���������������ݸ���
	//3.��posλ�ò���c
	//4.����_size��_size++������'\0'λ�ã�_str[_size]='\0'
	void Insert(const char c, size_t pos)//��posλ�ò����ַ�
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
		
	//1.���ռ䡣��������
	//2.��posλ�ÿ�ʼ�������������Ų��len��λ��
	//3.��str��posλ�ÿ�ʼ����
	//4.����_size
	void Insert(size_t pos, const char* str)//��posλ�ò����ַ���
	{
		size_t len = strlen(str);
		if (_size + len >= _capacity)
		{
			Reverse(_size + len);
		}
		size_t end = _size + len;
		//�Ӻ���ǰ��������
		while (pos + len - 1 < end)
		{
			_str[end] = _str[end - len];
			--end;
		}
		//��posλ�ÿ�ʼ����str
		for (size_t i = 0; i < len; i++)
		{
			_str[i + pos] = str[i];
		}
		_size += len;
	}

	//1.pos + len>_size���൱�ڴ�posλ�ÿ�ʼ���ַ�����ɾ������'\0'����pos��,����_size=pos,_str[size]='\0'
	//2.pos + len <= _size,��pos+lenλ�ÿ�ʼ��ǰŲ��len��λ�ã�����_size-=len,��ǰ���Ų
	void Erase(size_t pos, size_t len)
	{
		//�ж�λ���Ƿ�Ϸ�
		assert(pos < _size);
		//pos+len>_size,posλ�ú�Ԫ��ȫ��ɾ��
		if (pos + len > _size)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			//��ǰ����ƶ�
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