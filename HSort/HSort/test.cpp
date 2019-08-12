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
	//判断 root 是不是叶子节点
	int i = 2 * root + 1;

	if (i >= size) {
		return;
	}

	// 找到大孩子， 得考虑有没有右孩子的情况
	int max = i;
	if (i + 1 < size && array[i + 1] > array[i]) {
		max = i + 1;
	}

	// 大孩子的值 和 根的值比较
	if (array[root] >= array[max]) {
		return;
	}

	// 交换
	Swap(array + root, array + max);

	// 继续对 max 进行调整
	AdjustDown(array, size, max);
}

void HeapSort(int array[], int size) {
	// 大堆
	for (int i = (size - 2) / 2; i >= 0; i--) {
		AdjustDown(array, size, i);
	}

	for (int i = 0; i < size - 1; i++) {
		// 将根节点和最后一个节点交换，并进行向下调整
		Swap(&array[0], array + size - 1 - i);
		// 向下调整
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
