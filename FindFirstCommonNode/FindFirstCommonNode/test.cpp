#include <iostream>
using namespace std;
//��������ĵ�һ�������ڵ�

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};
class Solution {
public:
	ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
		ListNode* pNode1 = pHead1;
		ListNode* pNode2 = pHead2;
		//����ָ��ֱ������������
		while (pNode1 != pNode2)
		{
			pNode1 = ((pNode1 == nullptr) ? pHead2 : pNode1->next);
			pNode2 = ((pNode2 == nullptr) ? pHead1 : pNode2->next);
		}
		return pNode1;
	}
};