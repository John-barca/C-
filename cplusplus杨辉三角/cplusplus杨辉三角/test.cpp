#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
	//ÿһ��ͷβ����1��ÿһ�е�j����������һ��[j-1]+[j]��ֵ
	vector<vector<int>> generate(int numRows)
	{
		vector<vector<int>> vv;

		//�ȿ���������ǵĿռ�
		vv.resize(numRows);
		for (size_t i = 1; i <= numRows; ++i)
		{
			vv[i - 1].resize(i, 0);

			//ÿһ��ͷβ����0
			vv[i - 1][0] = 1;
			vv[i - 1][i - 1] = 1;
		}

		for (size_t i = 0; i < vv.size(); ++i)
		{
			for (size_t j = 0; j < vv[i].size(); ++i)
			{
				if (vv[i][j] == 0)
				{
					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
				}
			}
		}
		return vv;
	}
};