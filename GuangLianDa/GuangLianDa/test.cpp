// 链表的中间节点
class Solution {
	public ListNode middleNode(ListNode head) {
		if (head == null) return head;
		List<ListNode> list = new ArrayList<ListNode>();
		while (head != null) {
			list.add(head);
			head = head.next;
		}
		return list.get(list.size() / 2);
	}
}


// 盛水最多的容器
class Solution {
public:
	int maxArea(vector<int>& height) {
		if (height.size() <= 1) return -1;
		int i = 0, j = height.size() - 1, res = 0;
		while (i < j) {
			int h = min(height[i], height[j]);
			res = max(res, h * (j - i));
			if (height[i] < height[j]) ++i;
			else --j;
		}
		return res;
	}
};


// 被围绕的区域
int row, col;
public void solve(char[][] board) {
	if (board == null || board.length == 0)
		return;
	row = board.length;
	col = board[0].length;
	for (int i = 0; i < row; i++) {
		dfs(board, i, 0);
		dfs(board, i, col - 1);
	}
	for (int j = 0; j < col; j++) {
		dfs(board, 0, j);
		dfs(board, row - 1, j);
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == 'O')
				board[i][j] = 'X';
			if (board[i][j] == '-')
				board[i][j] = 'O';
		}
	}
	return;
}
public void dfs(char[][] board, int i, int j) {
	if (i < 0 || j < 0 || i >= row || j >= col || board[i][j] != 'O')
		return;
	board[i][j] = '-';
	dfs(board, i - 1, j);
	dfs(board, i + 1, j);
	dfs(board, i, j - 1);
	dfs(board, i, j + 1);
	return;
}

// 最低票价
class Solution {
	public int mincostTickets(int[] days, int[] costs) {
		// 将从新年到某一天的花过的所有钱数全部记录起来。
		int[] lastAllDaysCost = new int[366];
		//  days的下标，确保遍历365天时，以便于知道下次旅游的日期。
		int dayIdx = 0;
		// 日，月，年的花费。
		int ticketDay = costs[0];
		int ticketWeek = costs[1];
		int ticketMonth = costs[2];
		// 因为是第一天，所以过去的总花费为0
		lastAllDaysCost[0] = 0;
		// lastAllCost[i] 是截至到今年的第 i 天的总花费.

		// 模拟新年的第一天跑到旅行的最后一天。
		for (int today = 1; today <= 365; today++) {
			if (dayIdx >= days.length) {
				break;
			}
			// 判断今天是否属于旅行日。
			if (days[dayIdx] != today) {
				// 如果这一天不旅行那么直接把上一天的过去总花费拿过来直接使用。
				lastAllDaysCost[today] = lastAllDaysCost[today - 1];
				continue;
			}
			// 开始等待下一个待旅行的日子到来。
			dayIdx++;
			// 如果一月前，买了月票，会不会更便宜？
			// 如果一周前，买了周票，会不会更便宜？
			// 如果都不会的话，那我暂时先买日票试试呗。
			lastAllDaysCost[today] = Math.min(
				Math.min(
					lastAllDaysCost[Math.max(0, today - 1)] + ticketDay
					, lastAllDaysCost[Math.max(0, today - 7)] + ticketWeek)
				, lastAllDaysCost[Math.max(0, today - 30)] + ticketMonth);
		}
		return lastAllDaysCost[days[days.length - 1]];
	}
}