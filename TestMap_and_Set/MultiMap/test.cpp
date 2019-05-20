#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdlib.h>
using namespace std;


//set
//void test_set()
//{
//	//1.key��ģ�ͳ������ж��ڲ���? Ч�ʸ�,ʱ�临�Ӷ�O(logN)
//	//2.����+ȥ��
//	//֧����ɾ�飬��֧�ָ�
//	set<int> s1;
//	s1.insert(10);
//	s1.insert(8);
//	s1.insert(12);
//	s1.insert(17);
//	set<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		cout << *it1 << " ";//�õ�������ָ��Ŀռ䲻֧���޸�
//		++it1;
//	}
//	cout << endl;
//
//	for (auto e : s1)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//
//	int x;
//	x = 10;
//	auto retit = s1.find(x);	//O(logN)����ʱ�临�Ӷ�
//	s1.erase(retit);//������ɾ������Ϊ��Чλ�ã����򱨴�
//	s1.erase(x); //û�и�ֵ��ɾ��
//	if (retit != s1.end())
//	{
//		cout << "find it" << x << endl;
//	}
//	else
//	{
//		cout << "x���ڼ�����" << endl;
//	}
//
//	set<string> strs;
//	strs.insert("sort");
//	strs.insert("string");
//	strs.insert("insert");
//	for (auto e : strs)
//	{
//		cout << e << " ";
//	}
//}
//
//void test_multiset()
//{
//	//multiset:����ȥ�أ������ֵ����
//	//����
//	multiset<int> s2;
//	s2.insert(1);
//	s2.insert(3);
//	s2.insert(2);
//	s2.insert(1);
//	for (auto e : s2)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//}
//
//int main()
//{
//	//test_set();
//	test_multiset();
//	system("pause");
//	return 0;
//}

//map
void test_map()
{
	//pair��ֵ��

	map<string, string> dict;
	dict.insert(pair<string, string>("insert", "����"));
	dict.insert(pair<string, string>("sort", "����"));
	dict.insert(pair<string, string>("string", "�ַ���"));
	//map<string, string>::iterator dit = dict.begin();
	auto dit = dict.begin();
	while (dit != dict.end())
	{
		cout << dit->first << ":" << dit->second << endl;
		//cout << (*dit).first << ":" << (*dit).second << " ";
	}
	cout << endl;

	string str;
	while (cin >> str)
	{
		map<string, string>::iterator it = dict.find(str);
		if (it != dict.end())
		{
			cout << str << "->" << it->second << endl;
		}
		else
		{
			cout << "���ڴʿ���" << endl;
		}
	}
}

int main()
{
	test_map();
	system("pause");
	return 0;
}