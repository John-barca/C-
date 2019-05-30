#include <iostream>
#include <vector>
using namespace std;

class Board {
public:
	bool checkWon(vector<vector<int> > board) {
		// write code here
		int col = board.size();//行
		int row = board[0].size();//列
		for (int i = 0; i < col; i++) {
			for (int j = 0; j < row; j++) {
				if (j == 0) {//竖着或横着
					if (board[i][j] == 1)
					{
						if (board[i][j + 1] == board[i][j + 2] && board[i][j] == board[i][j + 1]) {
							return true;
						}
					}
					else if (board[i][j] == -1) {
						if (board[i][j + 2] == board[i][j + 2] && board[i][j] == board[i][j + 1]) {
							return false;
						}
					}
				}
				if (i == 0) {
					if (board[i][j] == 1) {
						if (board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i][j]) {
							return true;
						}
					}
					else if (board[i][j] == -1) {
						if (board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i][j]) {
							return false;
						}
					}
				}
				if (i == 1 && j == 1) {//对角线
					if (board[i][j] == 1) {
						if (board[i - 1][j - 1] == 1 && board[i + 1][j + 1] == 1)
						{
							return true;
						}
						else if (board[i - 1][j + 1] == 1 && board[i + 1][j - 1] == 1)
						{
							return true;
						}
					}
					else {
						break;//不可能赢
					}
				}
			}
		}
		return false;
	}
};