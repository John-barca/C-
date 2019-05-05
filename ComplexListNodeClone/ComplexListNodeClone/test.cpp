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
	void CloneNodes(RandomListNode* pHead)//����ԭʼ���������ڵ�N�����½ڵ㣬�����ýڵ�������ԭʼ�ڵ�֮��
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

	void ConnectSiblingNodes(RandomListNode* pHead)//�����½ڵ��Randomָ���Ƴ����Ľڵ�
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

	RandomListNode* ReconnectNodes(RandomListNode* pHead)//�������������λ����next������������ԭʼ������ż��λ����������Ϊ������
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