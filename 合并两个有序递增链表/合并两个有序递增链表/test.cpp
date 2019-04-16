#include <iostream>
using namespace std;


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};

class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		if (pHead1 == nullptr)
		{
			return pHead2;
		}
		if (pHead2 == nullptr)
		{
			return pHead1;
		}
		if ((pHead1 == nullptr) && (pHead2 == nullptr))
		{
			return nullptr;
		}
		ListNode* p1 = pHead1;
		ListNode* cur1 = pHead1;
		ListNode* p2 = pHead2;
		ListNode* cur2 = nullptr;
		while ((p1 != nullptr) && (p2 != nullptr))
		{
			if (p1->val > p2->val)
			{
				cur1->next = p2;
				cur2 = p2->next;
				p2->next = p1;
				p2 = cur2;
			}
			cur1 = p1;
			p1 = p1->next;
		}
		if (p2)
		{
			cur1->next = p2;
		}
		return pHead1;
	}
};