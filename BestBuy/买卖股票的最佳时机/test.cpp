#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		size_t sz = prices.size();
		int i, j;
		int temp = 0;
		for (i = 0; i < sz - 1; i++)
		{
			for (j = i + 1; j < sz; j++)
			{
				if (prices[j] - prices[i] < 0)
				{
					continue;
				}
				else if (prices[j] - prices[i] > temp)
				{
					temp = prices[j] - prices[i];
				}
			}
		}
		if (temp > 0)
		{
			return temp;
		}
		return 0;
	}
};