#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int a = 0;
		int b = 0;
		for (auto e : nums)
		{
			a = ~b & (a^e);
			b = ~a & (b^e);
		}
		return a;
	}
};