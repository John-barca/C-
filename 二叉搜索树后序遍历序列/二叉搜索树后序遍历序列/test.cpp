#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	bool VerifySquenceOfBST(vector<int> sequence) {
		int length = sequence.size();
		int i = 0;
		if (length == 0)
		{
			return false;
		}
		while (length--)
		{
			while (sequence[i] < sequence[length])
			{
				i++;
			}
			while (sequence[i] > sequence[length])
			{
				i++;
			}
			if (i < length)
			{
				return false;
			}
			i = 0;
		}
		return true;
	}
};