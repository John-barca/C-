#include <iostream>
#include <stdlib.h>
using namespace std;

//����������
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
		//����
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

		//ɾ��
		//1.ɾ��Ҷ�ӽڵ�
		if (cur->_pLeft == nullptr && cur->_pRight == nullptr)
		{
			//�Ƿ�ɾ��_root
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
				//ɾ��_root,��Ϊ��
				_root == nullptr;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_pLeft == nullptr) {
			if (cur != _root) {
				//ȷ����ǰ�ڵ��ڸ��׽ڵ���߻����ұߣ���Ӧλ����Ϊcur->_pRight
				if (parent->_pLeft == cur) {
					parent->_pLeft = cur->_pRight;
				}
				else {
					parent->_pRight = cur->_pRight;
				}
			}
			else {
				//����_root
				_root = _root->_pRight;
			}
			delete cur;
			cur = nullptr;
		}
		else if (cur->_pRight == nullptr) {//��֧��
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
			//cur���Һ��Ӷ�����
			//1.Ѱ���滻�ڵ�
			pNode pNext = cur->_pLeft;
			parent = cur;
			while (pNext->_pRight) {
				parent = pNext;
				pNext = pNext->_pRight;
			}

			//2.�û�
			cur->_data = pNext->_data;
			//ָ���û��ڵ��ָ������
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

			//3.ɾ���û��ڵ�
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