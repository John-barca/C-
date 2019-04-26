#include <iostream>
#include <vector>
using namespace std;

//顺时针打印矩阵元素


class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		int row = matrix.size(); //行
		int col = matrix[0].size(); //列
		vector<int> result; //输出序列
		if (row == 0 || col == 0)
		{
			return result;
		}
		int left = 0, top = 0, right = col - 1, bottom = row - 1; //左上 右下元素
		while ((left <= right) && (top <= bottom))
		{
			for (int i = left; i <= right; i++)
			{
				result.push_back(matrix[top][i]);
			}
			for (int i = top + 1; i <= bottom; i++)
			{
				result.push_back(matrix[i][right]);
			}
			if (top != bottom)
			{
				for (int i = right - 1; i >= left; i--)
				{
					result.push_back(matrix[bottom][i]);
				}
			}
			if (left != right)
			{
				for (int i = bottom - 1; i > top; i--)
				{
					result.push_back(matrix[i][left]);
				}
			}
			left++, right--, bottom--, top++;
		}
		return result;
	}
};