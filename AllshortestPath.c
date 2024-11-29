#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000001

int arr[1001][1001]; // 마을 간 거리 테이블
int visited[1001]; // 방문 여부

int main() 
{
	int n;
	
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	for (int k = 0; k < n; k++) 
	{
		for (int i = 0; i < n; i++)
		{
			if (k == i) continue;
			for (int j = 0; j < n; j++)
			{
				if (i == j || k == j) continue;

				if ((arr[i][j] == - 1 || arr[i][j] > arr[i][k] + arr[k][j]) && arr[i][k] != -1 && arr[k][j] != -1)
				{
					arr[i][j] = arr[i][k] + arr[k][j];
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if(j != n - 1) printf("%d ", arr[i][j]);
			else printf("%d\n", arr[i][j]);
		}
	}
}
