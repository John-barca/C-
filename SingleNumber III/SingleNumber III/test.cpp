#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		vector<int> res;
		sort(nums.begin(), nums.end());
		res.push_back(nums[0]);
		for (int i = 1; i < nums.size(); i++)
		{
			if (nums[i] == nums[i - 1])
			{
				res.pop_back();
			}
			else
			{
				res.push_back(nums[i]);
			}
		}
		return res;
	}
};