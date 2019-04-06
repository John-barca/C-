#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

//逆波兰表达式
//1.操作数入栈
//2.遇到操作符，从栈中取出操作符需要的操作数，取出操作数的位置应该为从右向左,
	//进行运算，运算的结果继续压栈，
//重复 1 2
//返回栈顶元素，即为最终表达式的结果
class Solution {
public:
	int evalRPN(vector<string>& tokens)
	{
		stack<int> s;
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
			{
				//最先取出来右操作数
				int right = s.top();
				s.pop();
				int left = s.top();
				s.pop();
				switch (tokens[i][0])
				{
				case '+':
					s.push(left + right);
					break;
				case '-':
					s.push(left - right);
					break;
				case '*':
					s.push(left*right);
					break;
				case '/':
					s.push(left / right);
					break;
				}
			}
			else
			{
				//遇到操作数压栈
				s.push(atoi(tokens[i].c_str()));
			}
			return s.top();
		}
	}
};