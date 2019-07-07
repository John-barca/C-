#include <iostream>
#include <string>
using namespace std;
char arr_Num[26] = { 'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U' };

int main() {
	string str;
	while (getline(cin, str)) {
		string init;
		auto it = str.begin();
		while (it != str.end()) {
			for (int i = 0; i < sizeof(arr_Num) / sizeof(arr_Num[0]); i++) {
				if (arr_Num[i] == *it) {
					if (i > 4) {
						cout << arr_Num[i - 5];
						break;
					}
					else {
						cout << arr_Num[21 + i];
						break;
					}
				}
				if (*it == ' ') {
					cout << ' ';
					break;
				}
			}
			it++;
		}
		cout << endl;
	}

	return 0;
}

//因子个数
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

/*
#if 0
int main(){
	int n;
	while(cin >> n){
		int count = 0;
		vector<int> num;
		for(int i = 2; i < n; i++){
			int tmp = 0;
			if(n % i == 0){
				count++;
				tmp = n / i;
			}
			for(int j = 2; j < tmp; j++){
				if(tmp % j == 0){
					count++;
					tmp /= j;
					j = 2;
				}
			}
			num.push_back(count);
		}
		sort(num.begin(), num.end());
		cout << num[num.size() - 1] << endl;;
	}

	return 0;
}
#endif*/

#if 0

int main() {
	int n;
	while (cin >> n) {
		int count = 0;
		for (int i = 2; i <= sqrt(n); i++) {
			if (n % i == 0) {
				while (n % i == 0) {
					n /= i;
				}
				count++;
			}
		}
		if (n != 1) {
			count++;
		}
		cout << count << endl;

	}

	return 0;
}
#endif