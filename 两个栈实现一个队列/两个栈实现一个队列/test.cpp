#include<iostream>
#include<stack>
using namespace std;

//����ջʵ��һ������
//1.���ջ��ֻ����������
//2.�����У�ֻ���������
//push���������push
//pop���������ջΪ�գ������ջ��Ԫ��ȫ��������
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