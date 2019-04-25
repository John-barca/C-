#include <iostream>
#include <stack>
using namespace std;
//°üº¬Minº¯ÊýµÄÕ»
class Solution {
public:
	void push(int value) {
		stackInt.push(value);
		if (stackMin.empty())
		{
			stackMin.push(value);
		}
		else if (stackMin.top() < value) {
			stackMin.push(stackMin.top());
		}
		else
		{
			stackMin.push(value);
		}
	}
	void pop() {
		if (!stackInt.empty())
		{
			stackInt.pop();
			stackMin.pop();
		}
	}
	int top() {
		return stackInt.top();
	}
	int min() {
		return stackMin.top();
	}
private:
	stack<int> stackMin;
	stack<int> stackInt;
};