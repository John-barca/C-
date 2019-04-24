#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if ((pre.size() == 0) && (vin.size() == 0))
		{
			return nullptr;
		}
		vector<int> left_in, left_pre, right_pre, right_in;
		int prelen = pre.size();
		int inlen = vin.size();
		TreeNode* root = new TreeNode(pre[0]);
		int gen = 0;
		for (int i = 0; i < inlen; i++)
		{
			if (pre[0] == vin[i])
			{
				gen = i;
				break;
			}
		}
		for (int i = 0; i < gen; i++)
		{
			left_in.push_back(vin[i]);
			left_pre.push_back(pre[i + 1]);
		}
		for (int i = gen + 1; i < inlen; i++)
		{
			right_in.push_back(vin[i]);
			right_pre.push_back(pre[i]);
		}

		root->left = reConstructBinaryTree(left_pre, left_in);
		root->right = reConstructBinaryTree(right_pre, right_in);
		return root;

	}
};