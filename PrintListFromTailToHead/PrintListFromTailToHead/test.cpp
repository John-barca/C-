#include <vector>
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
	ListNode* ReverseList(ListNode* head)
	{
		ListNode* p = head;
		ListNode* q = head->next;
		ListNode* cur = nullptr;
		while (q != nullptr)
		{
			p->next = cur;
			cur = q->next;
			q->next = p;
			p = cur;
			cur = q;
			q = p->next;
		}
		p->next = cur;
		return p;
	}
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> V;
		if (head == nullptr)
		{
			return V;
		}
		ListNode* phead = ReverseList(head);
		ListNode* cur = phead;
		int i = 0;
		while (cur != nullptr)
		{
			V.push_back(cur->val);
			cur = cur->next;
		}
		return V;
	}
};

int main()
{
	ListNode* cur1 = new ListNode(0);
	ListNode* cur2 = new ListNode(1);
	ListNode* cur3 = new ListNode(2);
	ListNode* cur4 = new ListNode(3);
	ListNode* cur5 = new ListNode(4);
	cur1->next = cur2;
	cur2->next = cur3;
	cur3->next = cur4;
	cur4->next = cur5;
	cur5->next = nullptr;
	Solution().printListFromTailToHead(cur1);

	return 0;
}

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> V;
		vector<int> ArrayList;
		if (head == nullptr)
		{
			return V;
		}
		ListNode* cur = head;
		while (cur != nullptr)
		{
			V.push_back(cur->val);
			cur = cur->next;
		}
		vector<int>::reverse_iterator vit = V.rbegin();
		while (vit != V.rend())
		{
			ArrayList.push_back(*vit);
			vit++;
		}
		return ArrayList;
	}
};