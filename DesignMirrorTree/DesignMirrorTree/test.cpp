#include <iostream>
using namespace std;

//���������任Ϊ���ľ��������
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
	void Mirror(TreeNode *pRoot) {
		if (pRoot == nullptr)
		{
			return;
		}
		TreeNode* cur = pRoot->left;
		pRoot->left = pRoot->right;
		pRoot->right = cur;
		Mirror(pRoot->left);
		Mirror(pRoot->right);
	}
};