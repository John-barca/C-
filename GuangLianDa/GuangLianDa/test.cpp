// ������м�ڵ�
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


// ʢˮ��������
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


// ��Χ�Ƶ�����
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

// ���Ʊ��
class Solution {
	public int mincostTickets(int[] days, int[] costs) {
		// �������굽ĳһ��Ļ���������Ǯ��ȫ����¼������
		int[] lastAllDaysCost = new int[366];
		//  days���±꣬ȷ������365��ʱ���Ա���֪���´����ε����ڡ�
		int dayIdx = 0;
		// �գ��£���Ļ��ѡ�
		int ticketDay = costs[0];
		int ticketWeek = costs[1];
		int ticketMonth = costs[2];
		// ��Ϊ�ǵ�һ�죬���Թ�ȥ���ܻ���Ϊ0
		lastAllDaysCost[0] = 0;
		// lastAllCost[i] �ǽ���������ĵ� i ����ܻ���.

		// ģ������ĵ�һ���ܵ����е����һ�졣
		for (int today = 1; today <= 365; today++) {
			if (dayIdx >= days.length) {
				break;
			}
			// �жϽ����Ƿ����������ա�
			if (days[dayIdx] != today) {
				// �����һ�첻������ôֱ�Ӱ���һ��Ĺ�ȥ�ܻ����ù���ֱ��ʹ�á�
				lastAllDaysCost[today] = lastAllDaysCost[today - 1];
				continue;
			}
			// ��ʼ�ȴ���һ�������е����ӵ�����
			dayIdx++;
			// ���һ��ǰ��������Ʊ���᲻������ˣ�
			// ���һ��ǰ��������Ʊ���᲻������ˣ�
			// ���������Ļ���������ʱ������Ʊ�����¡�
			lastAllDaysCost[today] = Math.min(
				Math.min(
					lastAllDaysCost[Math.max(0, today - 1)] + ticketDay
					, lastAllDaysCost[Math.max(0, today - 7)] + ticketWeek)
				, lastAllDaysCost[Math.max(0, today - 30)] + ticketMonth);
		}
		return lastAllDaysCost[days[days.length - 1]];
	}
}