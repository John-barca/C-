#include <iostream>
#include <vector>
#include <ctime>

void EchoVector(std::vector<int>& vec) {
	for (int i = 0; i < vec.size() - 1; i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << vec[vec.size() - 1] << std::endl;
}

void CinV(std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cin >> vec[i];
	}
}


void _Merge(std::vector<int>& vec, int left, int div, int right, int* extra) {
	int sz = right - left;

	// ���������������ʼ�±�
	int left_index = left;
	int right_index = div;

	// �¿��ٿռ����ʼ�±�
	int index = 0;

	while (left_index < div && right_index < right) {
		if (vec[left_index] < vec[right_index]) {
			extra[index] = vec[left_index];
			left_index++;
		}
		else {
			extra[index] = vec[right_index];
			right_index++;
		}

		index++;
	}

	while (left_index < div) {
		extra[index++] = vec[left_index++];
	}
	while (right_index < right) {
		extra[index++] = vec[right_index++];
	}

	for (int i = 0; i < sz; i++) {
		vec[left + i] = extra[i];
	}

}

void Merge(std::vector<int>& vec, int left, int right, int* extra) {
	if (left + 1 == right) {
		// �����ڻ�ʣһ����������
		return;
	}
	if (left >= right) {
		// ������û����
		return;
	}

	// ����Ϊ����ҿ�
	// [left, div)
	// [div, right)
	int div = (left + right) / 2;
	Merge(vec, left, div, extra);
	Merge(vec, div, right, extra);

	// �ϲ�������������
	_Merge(vec, left, div, right, extra);
}

void MergeSort(std::vector<int>& vec) {
	int size = vec.size();
	int* extra = new int[vec.size()];

	Merge(vec, 0, vec.size(), extra);
	delete[] extra;
}


int main() {
	std::vector<int> vec;
	int N;
	while (std::cin >> N) {
		vec.resize(N);
		CinV(vec);

		EchoVector(vec);
	    MergeSort(vec);
		EchoVector(vec);
	}


	EchoVector(vec);

	return 0;
}