#include <iostream>
#include <vector>
using namespace std;
//二叉树中和为某一值的路径

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};

class Solution {
public:
	vector<vector<int>> Path;
	vector<int> tmp;
	vector<vector<int> > FindPath(TreeNode* root, int expectNumber) {
		if (root == nullptr)
		{
			return Path;
		}
		tmp.push_back(root->val);
		if (expectNumber - root->val == 0 && root->left == nullptr && root->right == nullptr)
		{
			Path.push_back(tmp);
		}
		FindPath(root->left, expectNumber - root->val);
		FindPath(root->right, expectNumber - root->val);
		if (tmp.size() != 0)
		{
			tmp.pop_back();
		}
		return Path;
	}
};