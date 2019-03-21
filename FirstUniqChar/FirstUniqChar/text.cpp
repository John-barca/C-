#include <iostream>
using namespace std;

class Solution
{
public:
	int firstUniqChar(string s) {
		int hashtable[256] = { 0 };
		for (auto e : s)
		{
			hashtable[e]++;
		}
		for (size_t i = 0; i < s.size(); i++)
		{
			if (hashtable[s[i]] == 1)
			{
				return i;
			}
		}
		return -1;
	}
};