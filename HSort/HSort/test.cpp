#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void PrintArray(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d\t", array[i]);
	}
	printf("\n");
}

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void AdjustDown(int array[], int size, int root) {
	//�ж� root �ǲ���Ҷ�ӽڵ�
	int i = 2 * root + 1;

	if (i >= size) {
		return;
	}

	// �ҵ����ӣ� �ÿ�����û���Һ��ӵ����
	int max = i;
	if (i + 1 < size && array[i + 1] > array[i]) {
		max = i + 1;
	}

	// ���ӵ�ֵ �� ����ֵ�Ƚ�
	if (array[root] >= array[max]) {
		return;
	}

	// ����
	Swap(array + root, array + max);

	// ������ max ���е���
	AdjustDown(array, size, max);
}

void HeapSort(int array[], int size) {
	// ���
	for (int i = (size - 2) / 2; i >= 0; i--) {
		AdjustDown(array, size, i);
	}

	for (int i = 0; i < size - 1; i++) {
		// �����ڵ�����һ���ڵ㽻�������������µ���
		Swap(&array[0], array + size - 1 - i);
		// ���µ���
		AdjustDown(array, size - 1 - i, 0);
	}
}


int main()
{
	int array[] = { 95,87,65,91,12,18,13,14,5,4 };
	int size = sizeof(array) / sizeof(array[0]);
	PrintArray(array, size);
	HeapSort(array, size);
	
	PrintArray(array, size);

	system("pause");
	return 0;
}
