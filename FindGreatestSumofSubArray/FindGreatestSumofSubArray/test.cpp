#include <iostream>
#include <vector>
using namespace std;
//连续子数组的最大和


class Solution {
public:
	int FindGreatestSumOfSubArray(vector<int> array) {
		if (array.size() == 0)
		{
			return 0;
		}
		int nCurSum = 0;
		int nGreatestSum = array[0];
		for (int i = 0; i < array.size(); i++)
		{
			if (nCurSum <= 0)
			{
				nCurSum = array[i];
			}
			else {
				nCurSum += array[i];
			}
			if (nCurSum > nGreatestSum)
			{
				nGreatestSum = nCurSum;
			}
		}
		return nGreatestSum;
	}
};