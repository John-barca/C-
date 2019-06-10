//#include <iostream>
//#include <vector>
//using namespace std;
//
//int CountofB(int num) {
//	int sum = 0;
//	if (num < 2) {
//		return 0;
//	}
//	if (num == 2) {
//		return 1;
//	}
//	else {
//		sum = num / 3;
//	}
//	return CountofB(sum + num % 3) + sum;
//}
//
//vector<int> Check_CountofBottle(vector<int> Num) {
//	vector<int> result;
//	result.resize(Num.size());
//	for (size_t i = 0; i < Num.size(); i++) {
//		if (Num[i] != 0) {
//			result[i] = CountofB(Num[i]);
//		}
//		else
//			break;
//	}
//	return result;
//}
//
//int main() {
//	vector<int> Num;
//	Num.resize(11);
//	for (int i = 0; i < Num.size(); i++) {
//		cin >> Num[i];
//		if (Num[i] == 0)
//			break;
//	}
//
//	vector<int> result = Check_CountofBottle(Num);
//	for (int i = 0; i < result.size(); i++) {
//		cout << result[i] << endl;
//	}
//	system("pause");
//	return 0;
//}
//int main() {
//	int num;
//	while (cin >> num) {
//		num = CountofB(num);
//		cout << num << endl;
//	}
//}
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

//string Find_longest(string f_str, string s_str) {
	//string result;//最长子串
	//int length = 0;//记录长度
	//int Max = 0;//最长子串的长度
	//int tmp = 0;
	//for (int i = 0; i < f_str.size(); i++) {
	//	for (int j = 0; j < s_str.size(); j++) {
	//		if (f_str[i] == s_str[j]) {
	//			i++;
	//			tmp++;
	//		}
	//		else {
	//			if (tmp > Max) {
	//				Max = tmp;
	//				length = j - 1;
	//			}
	//			
	//			continue;
	//		}
	//	}
	//	i = i - tmp;
	//	tmp = 0;
	//}
	//for (int i = 0; i < Max ; ++i) {
	//	result.operator +=(s_str[length - Max + 1]);
	//	length++;
	//}
	//return result;
//	string result;
//	if (f_str.size() > s_str.size()) {
//		swap(f_str, s_str);
//	}
//	for (int i = 0; i < f_str.size(); i++) {
//		for (int j = i; j < f_str.size(); j++) {
//			string temp = f_str.substr(i, j - i + 1);
//			if ((s_str.find(temp)) < 0) {
//				break;
//			}
//			else if (temp.size() > result.size()) {
//				result = temp;
//			}
//		}
//	}
//	return result;
//}

int main() {
	string f_str;
	string s_str;
	while (cin >> f_str >> s_str)
	{
		

		string result;
		if (f_str.size() > s_str.size()) {
			swap(f_str, s_str);
		}
		for (int i = 0; i < f_str.size(); i++) {
			for (int j = i; j < f_str.size(); j++) {
				string temp = f_str.substr(i, j - i + 1);
				if (int(s_str.find(temp)) < 0) {
					break;
				}
				else if (temp.size() > result.size()) {
					result = temp;
				}
			}
		}
		cout << result << endl;
	}
	return 0;
}
