//#include <iostream>
//#include <vector>
//using namespace std;
//
//vector<int> ChangeNum(vector<int>& Play_Num) {
//	vector<int> tmp;
//	//tmp.resize(Play_Num.size());
//	int count = 0;
//	while (count < Play_Num.size() / 2) {
//		//if (count == 0 || count % 2 == 0) {
//			tmp.push_back(Play_Num[count]);
//			tmp.push_back(Play_Num[count + Play_Num.size() / 2]);
//		/*else {
//			tmp.push_back(Play_Num[count + Play_Num.size() / 2]);
//			tmp.push_back(Play_Num[count]);
//		}*/
//
//		count++;
//	}
//	/*if (k - 1 > 0) {
//		tmp = ChangeNum(tmp, k - 1);
//	}*/
//	return tmp;
//}
//
//int main() {
//	int T;
//	cin >> T;
//	while (T--) {
//		int n, k;
//		cin >> n >> k;
//		vector<int> Play_Num;
//		//Play_Num.resize(2 * n);
//		int i = 0;
//		for (; i < 2 * n; i++) {
//			int _s;
//			cin >> _s;
//			Play_Num.push_back(_s);	
//		}
//		while (k--) {
//			Play_Num = ChangeNum(Play_Num);
//		}
//		auto it = Play_Num.begin();
//		for (; it != Play_Num.end() - 1; it++) {
//			cout << *it << " ";
//		}
//		cout << Play_Num[Play_Num.size() - 1] << endl;
//	}
//	system("pause");
//	return 0;
//}


#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	int Num_Song;
	while (cin >> Num_Song) {
		string command;//记录命令
		cin >> command;
		vector<int> Menu;//记录歌曲
		int result;//记录输出结果
		int tmp = 0;//记录位置
		int list = 0;//记录在当前菜单的第几位
		for (int i = 0; i < Num_Song; i++) {
			Menu.push_back(i + 1);
		}
		for (int i = 0; i < command.size(); i++) {
			if (Num_Song <= 4) {
				
				if (command[i] == 'U') {
					if (tmp == 0) {
						result = Menu[Num_Song - 1];
						tmp = Num_Song - 1;
					}
					else{
						result = Menu[tmp - 1];
						tmp = tmp - 1;
					}
				}
				else if (command[i] == 'D') {
					if (tmp == Num_Song - 1) {
						result = Menu[0];
						tmp = 0;
					}
					else {
						result = Menu[tmp + 1];
						tmp = tmp + 1;
					}
				}
			}
			else if (Num_Song > 4) {
				if (command[i] == 'U') {
					if (tmp == 0) {
						result = Menu[Num_Song - 1];
						tmp = Num_Song - 1;
						list = 3;
					}
					else {
						result = Menu[tmp - 1];
						tmp = tmp - 1;
						if (list == 0) {
							continue;
						}
						list--;
					}
				}
				else if (command[i] == 'D') {
					if (tmp == Num_Song - 1) {
						result = Menu[0];
						tmp = 0;
						list = 0;
					}
					else {
						result = Menu[tmp + 1];
						tmp = tmp + 1;
						if (list == 3) {
							continue;
						}
						list++;
					}
				}
			}
		}
		if (Num_Song <= 4) {
			for (int i = 0; i < Menu.size(); i++) {
				cout << Menu[i] << " ";
			}
			cout << endl;
			cout << result;
		}
		else {
			for (int i = 0; i < 4; i++) {
				cout << Menu[tmp - list + i] << " ";
			}
			cout << endl;
			cout << result;
		}

	}
	system("pause");
	return 0;
}