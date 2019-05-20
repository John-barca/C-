#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stdlib.h>
using namespace std;


//set
//void test_set()
//{
//	//1.key的模型场景，判断在不在? 效率高,时间复杂度O(logN)
//	//2.排序+去重
//	//支持增删查，不支持改
//	set<int> s1;
//	s1.insert(10);
//	s1.insert(8);
//	s1.insert(12);
//	s1.insert(17);
//	set<int>::iterator it1 = s1.begin();
//	while (it1 != s1.end())
//	{
//		cout << *it1 << " ";//该迭代器所指向的空间不支持修改
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
//	auto retit = s1.find(x);	//O(logN)查找时间复杂度
//	s1.erase(retit);//迭代器删除必须为有效位置，否则报错
//	s1.erase(x); //没有该值则不删除
//	if (retit != s1.end())
//	{
//		cout << "find it" << x << endl;
//	}
//	else
//	{
//		cout << "x不在集合中" << endl;
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
//	//multiset:不会去重，允许键值冗余
//	//排序
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
	//pair键值对

	map<string, string> dict;
	dict.insert(pair<string, string>("insert", "插入"));
	dict.insert(pair<string, string>("sort", "排序"));
	dict.insert(pair<string, string>("string", "字符串"));
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
			cout << "不在词库中" << endl;
		}
	}
}

int main()
{
	test_map();
	system("pause");
	return 0;
}