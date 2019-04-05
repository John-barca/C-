#include <iostream>
#include <stack>
using namespace std;

class MinStack {
public:
	MinStack()
	{}
	void push(int x)
	{
		_s.push(x);
		if (_min.empty() || x <= _min.top())
		{
			_min.push(x);
		}
	}
	void pop()
	{
		if (_min.top() == _s.top())
		{
			_min.pop();
		}
		_s.pop();
	}
	int top()
	{
		return _s.top();
	}
	int GetMin()
	{
		return _min.top();
	}
private:
	stack<int> _s;
	stack<int> _min;
};