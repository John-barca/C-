#include <iostream>
using namespace std;


struct RandomListNode {
	int label;
	struct RandomListNode *next, *random;
	RandomListNode(int x) :
			label(x), next(NULL), random(NULL) {
	}
};

class Solution {
public:
	void CloneNodes(RandomListNode* pHead)//复制原始链表的任意节点N创建新节点，并将该节点连接在原始节点之后
	{
		RandomListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			RandomListNode* pCloned = new RandomListNode(0);
			pCloned->label = pNode->label;
			pCloned->next = pNode->next;
			pCloned->random = nullptr;

			pNode->next = pCloned;
			pNode = pCloned->next;
		}
	}

	void ConnectSiblingNodes(RandomListNode* pHead)//设置新节点的Random指向复制出来的节点
	{
		RandomListNode* pNode = pHead;
		while (pNode != nullptr)
		{
			RandomListNode* pCloned = pNode->next;
			if (pNode->random != nullptr)
			{
				pCloned->random = pNode->random->next;
			}
			pNode = pCloned->next;
		}
	}

	RandomListNode* ReconnectNodes(RandomListNode* pHead)//将新链表的奇数位置用next连接起来就是原始链表，将偶数位置连接起来为新链表
	{
		RandomListNode* pNode = pHead;
		RandomListNode* pClonedHead = nullptr;
		RandomListNode* pClonedNode = nullptr;

		if (pNode != nullptr)
		{
			pClonedHead = pClonedNode = pNode->next;
			pNode->next = pClonedNode->next;
			pNode = pNode->next;
		}

		while (pNode != nullptr)
		{
			pClonedNode->next = pNode->next;
			pClonedNode = pClonedNode->next;
			pNode->next = pClonedNode->next;
			pNode = pNode->next;
		}

		return pClonedHead;
	}

	RandomListNode* Clone(RandomListNode* pHead)
	{
		CloneNodes(pHead);
		ConnectSiblingNodes(pHead);
		return ReconnectNodes(pHead);
	}
};