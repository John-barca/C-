#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x)
		:val(x)
		,left(NULL)
		,right(NULL)
	{}
};

class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> result = {};
		if (root == nullptr)
		{
			return result;
		}
		std::stack<TreeNode*> stackNode;
		stackNode.push(root);
		while (!stackNode.empty())
		{
			TreeNode* Node = stackNode.top();
			if (Node->left != nullptr)
			{
				stackNode.push(Node->left);
				Node->left = nullptr;
			}
			else if (Node->right != nullptr)
			{
				result.push_back(Node->val);
				stackNode.pop();
				stackNode.push(Node->right);
				Node->right = nullptr;
			}
			else
			{
				result.push_back(Node->val);
				stackNode.pop();
			}
		}
		return result;
	}
};