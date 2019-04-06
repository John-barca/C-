#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

//�沨�����ʽ
//1.��������ջ
//2.��������������ջ��ȡ����������Ҫ�Ĳ�������ȡ����������λ��Ӧ��Ϊ��������,
	//�������㣬����Ľ������ѹջ��
//�ظ� 1 2
//����ջ��Ԫ�أ���Ϊ���ձ��ʽ�Ľ��
class Solution {
public:
	int evalRPN(vector<string>& tokens)
	{
		stack<int> s;
		for (int i = 0; i < tokens.size(); i++)
		{
			if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
			{
				//����ȡ�����Ҳ�����
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
				//����������ѹջ
				s.push(atoi(tokens[i].c_str()));
			}
			return s.top();
		}
	}
};