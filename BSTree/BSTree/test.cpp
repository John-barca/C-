#include <iostream>
#include <stdlib.h>
using namespace std;

//二叉搜索树
template<class T>
struct BSTNode {
	BSTNode(const T& val = T())
		:_data(val)
		,_pLeft(nullptr)
		,_pRight(nullptr)
	{}

	T _data;
	BSTNode<T>* _pLeft;
	BSTNode<T>* _pRight;
};

template<class T>
class BSTree {
public:
	typedef BSTNode<T> Node;
	typedef Node* pNode;

	BSTree(const pNode root = nullptr)
		:_root(root)
	{}

	pNode find(const T& val)
	{
		if (_root == nullptr)
		{
			return nullptr;
		}
		pNode cur = _root;
		while (cur) {
			if (cur->_data == val)
			{
				return cur;
			}
			else if (cur->_data > val) {
				cur = cur->_pLeft;
			}
			else {
				cur = cur->_pRight;
			}
		}
		return nullptr;
	}

	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur)
		{
			parent = cur;
			if (cur->_data > val) {
				cur = cur->_pLeft;
			}
			else if (cur->_data < val)
			{
				cur = cur->_pRight;
			}
			else {
				return false;
			}
		}
		pNode newNode = new Node(val);
		if (parent->_data > val) {
			parent->_pLeft = newNode;
		}
		else {
			parent->_pRight = newNode;
		}
		return true;
	}

	void inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	void _Inorder(pNode root)
	{
		if (root) {
			_Inorder(root->_pLeft);
			cout << root->_data << " ";
			_Inorder(root->_pRight);
		}
	}

	bool erase(const T& val)
	{
		//搜索
		if (_root == nullptr) {
			return nullptr;
		}
		pNode cur = _root;
		pNode parent = nullptr;
		while (cur)
		{
			if (cur->_data == val)
			{
				break;
			}
			else if (cur->_data > val) {
				parent = cur;
				cur = cur->_pLeft;
			}
			else if (cur->_data < val) {
				parent = cur;
				cur = cur->_pRight;
			}
		}

		//删除
		//1.删除叶子节点
		if (cur->_pLeft == nullptr && cur->_pRight == nullptr)
		{
			//是否删除_root
			if (cur != _root) {
				if (parent->_pLeft == cur)
				{
					parent->_pLeft = nullptr;
				}
				else if (parent->_pRight == cur) {
					parent->_pRight == nullptr;
				}
			}
			else {
				//删除_root,树为空
				_root == nullptr;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_pLeft == nullptr) {
			if (cur != _root) {
				//确定当前节点在父亲节点左边还是右边，对应位置设为cur->_pRight
				if (parent->_pLeft == cur) {
					parent->_pLeft = cur->_pRight;
				}
				else {
					parent->_pRight = cur->_pRight;
				}
			}
			else {
				//更新_root
				_root = _root->_pRight;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_pRight == nullptr) {//左单支树
			if (cur != _root) {
				if (parent->_pLeft == cur)
					parent->_pLeft = cur->_pLeft;
				else {
					parent->_pRight = cur->_pLeft;
				}
			}
			else {
				_root = _root->_pLeft;
			}
			delete cur;
			cur = nullptr;
		}
		else {
			//cur左右孩子都存在
			//1.寻找替换节点
			pNode pNext = cur->_pLeft;
			parent = cur;
			while (pNext->_pRight) {
				parent = pNext;
				pNext = pNext->_pRight;
			}

			//2.置换
			cur->_data = pNext->_data;
			//指向置换节点的指针悬空
			if (parent->_pRight == pNext) {
				parent->_pRight = nullptr;
			}
			else {
				if (pNext->_pLeft != nullptr) {
					parent->_pLeft = pNext->_pLeft;
				}
				else {
					parent->_pLeft = nullptr;
				}
			}

			//3.删除置换节点
			delete pNext;
			pNext = nullptr;
		}
		return true;
	}

	~BSTree()
	{
		Distroy(_root);
	}

	void Distroy(pNode root) {
		if (root)
		{
			Distroy(root->_pLeft);
			Distroy(root->_pRight);
			delete root;
			root = nullptr;
		}
	}

private:
	pNode _root;
};

void TestTree()
{
	BSTree<int> Tree;
	Tree.insert(5);
	Tree.insert(3);
	Tree.insert(1);
	Tree.insert(4);
	Tree.insert(0);
	Tree.insert(7);
	Tree.insert(6);
	Tree.insert(8);
	Tree.insert(9);
	Tree.inorder();
	Tree.erase(3);
	Tree.inorder();
}

int main()
{
	TestTree();
	system("pause");
	return 0;
}