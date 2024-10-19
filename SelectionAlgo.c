#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void MySwap(int* arr, int index1, int index2)
{
    // arr에 있는 index1 과 index2에 있는 값을 swap하는 함수

    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int Median_of_3(int* arr, int low, int high) {
    // low, mid, high에 있는 값들을, 정렬하여 mid에 중앙값이 위치하도록 한다.
    // 반환은 mid 인덱스 값을 반환한다.
    // 이는 최악의 경우를 피하기 위해서 피벗을 중앙값으로 하기 위한 함수이다.

    int mid = (low + high) / 2; // 중앙값을 찾기 위한 mid
    if (arr[high] < arr[low]) MySwap(arr, low, high);
    if (arr[mid] < arr[low]) MySwap(arr, low, mid);
    if (arr[high] < arr[mid]) MySwap(arr, mid, high);
    return mid;
}

int SelectionK(int* arr, int begin, int end, int k) 
{
	int mid = Median_of_3(arr, begin, end);

	MySwap(arr, begin, mid);

	int pivot = begin;

	int low = pivot + 1;
	int high = end;

    while (low <= high) 
    {
		while (low <= high && arr[low] <= arr[pivot])
			low++; // low는 피벗보다 큰 값을 색출

		while (low <= high && arr[high] >= arr[pivot])
			high--; // high는 피벗보다 작은 값을 색출

		if (low < high)
		{
			MySwap(arr, low, high); // low와 high의 값을 바꿈으로써 partition을 진행
			low++;
			high--;
		}
    }

	MySwap(arr, high, pivot);

	// 현재 진짜 pivot은 high

	int lowCount = high - begin;

	if(k == lowCount + 1)
	{
		return arr[high];
	}
	else if (k > lowCount + 1) 
	{
		return SelectionK(arr, high + 1, end, k - lowCount - 1);
	}
	else 
	{
		return SelectionK(arr, begin, high - 1, k);
	}
}

int main()
{
	int n;
	scanf("%d", &n); // 배열의 크기

	int* arr = (int*)malloc(sizeof(int) * n); // 배열 동적할당

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	int k;

	scanf("%d", &k);

	printf("%d", SelectionK(arr, 0, n - 1, k));

	free(arr);

	return 0;
}
