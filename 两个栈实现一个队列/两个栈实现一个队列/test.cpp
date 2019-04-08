#include<iostream>
#include<stack>
using namespace std;

//两个栈实现一个队列
//1.入队栈：只负责入数据
//2.出队列：只负责出数据
//push：给入队列push
//pop：如果出队栈为空，把入队栈的元素全部倒过来
class MyQueue
{
public:
	MyQueue()
	{}
	void push(int x)
	{
		pushS.push(x);
	}
	int pop()
	{
		if (popS.empty())
		{
			while (!pushS.empty())
			{
				pops.push(pushS.top());
				pushS.pop();
			}
		}
		int val = popS.top();
		popS.pop();
		return val;
	}
	int peek()
	{
		if (pushS.empty())
		{
			while (!popS.empty())
			{
				popS.push(pushS.top());
				pushS.pop();
			}
		}
		return popS.top();
	}
	bool empty()
	{
		return pushS.empty() && popS.empty();
	}

private:
	stack<int> pushS;
	stack<int> popS;
};