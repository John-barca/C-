#include <iostream>
using namespace std;

int main() {
	double n, r;
	while (cin >> n >> r) {
		if (n <= 6.28 * r) {
			cout << "Yes" << endl;
		}
		else {
			cout << "No" << endl;
		}
	}

	return 0;
}