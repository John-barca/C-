#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


int TheGreater(int num[], int length)
{
	vector<int> SortNum;
	
	if (length == 0)
		return 0;
	if (length == 1)
		return num[0];
	if (length == 2)
		return num[0] * num[1];

	for (int i = 0; i < length; i++)
	{
		SortNum.push_back(num[i]);
	}
	vector<int>::iterator it = SortNum.begin();
	sort(it, SortNum.end());
	int Number = SortNum[SortNum.size() - 1] * SortNum[SortNum.size() - 2] * SortNum[SortNum.size() - 3];
	return Number;
}

//int main()
//{
//	int num[] = { 1,2,4,5,10,9 };
//	int Sum;
//	int length = sizeof(num) / sizeof(num[0]);
//	Sum = TheGreater(num, length);
//	cout << Sum << endl;
//
//	system("pause");
//	return 0;
//}

int main()
{
	int num[] = {0};
	int n;
	cin >> n;
	for (int i = 0; i < n ; i++)
	{
		cin >> num[i];
	}
	int sum = TheGreater(num, n);
	cout << sum << " ";
	system("pause");
	return 0;
}