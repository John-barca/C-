#include <iostream>
#include <list>
using namespace std;

struct ListNode {
    int val;
	ListNode *next;
	ListNode(int x)
		: val(x)
		, next(NULL)
		{}
};
class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		int pos = 0;
		if (head->next == NULL)
		{
			cout << "no cycle" << endl;
			pos = -1;
			return nullptr;
		}
		ListNode* fast = head;
		ListNode* slow = head;
		do
		{
			fast = fast->next->next;
			slow = slow->next;
		} while (slow != fast && fast);
		if (fast == nullptr)
		{
			pos = -1;
			cout << "no cycle" << endl;
			return nullptr;
		}
		else if (fast == slow)
		{
			fast = head;
			while (fast != slow)
			{
				fast = fast->next;
				slow = slow->next;
				++pos;
			}
			cout << "tail connects to node index:" << pos << endl;
			return fast;
		}
		return nullptr;
	}
};

int main()
{
	ListNode* _head = new ListNode(3);
	ListNode* second = new ListNode(2);
	ListNode* third = new ListNode(0);
	ListNode* fourth = new ListNode(-4);

	_head->next = second;
	second->next = third;
	third->next = fourth;

	fourth->next = second;
	Solution().detectCycle(_head);
	return 0;
}