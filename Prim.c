#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int isInTree[10000];

typedef struct edge
{
	int start;
	int weight;
} Edge;

int adj[10000][10000];
Edge weightArr[10000];

int main()
{
	int vertexCount, edgeCount;

	scanf("%d %d", &vertexCount, &edgeCount);

	for (int i = 0; i < vertexCount; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			adj[i][j] = -1;
		}
	}

	for (int i = 0; i < edgeCount; i++)
	{
		int edge_start, edge_end, weight;
		scanf("%d %d %d", &edge_start, &edge_end, &weight);

		adj[edge_start][edge_end] = weight;
		adj[edge_end][edge_start] = weight;
	}

	isInTree[0] = 1;

	for (int i = 1; i < vertexCount; i++)
	{
		weightArr[i].start = -1;
		weightArr[i].weight = 10000000;
	}

	int minIndex = 0;

	int min = 10000000;


	isInTree[minIndex] = 1;


	for (int i = 0; i < vertexCount - 1; i++)
	{
		for (int j = 0; j < vertexCount; j++)
		{
			// 기존의 가중치보다 큰 경우만 최신화
			if ( !isInTree[j]  && adj[minIndex][j] != -1  && adj[minIndex][j] < weightArr[j].weight)
			{
				weightArr[j].start = minIndex;
				weightArr[j].weight = adj[minIndex][j];
			}
		}

		min = 10000000;

		for (int j = 1; j < vertexCount; j++)
		{
			if (weightArr[j].weight < min && !isInTree[j])
			{
				min = weightArr[j].weight;
				minIndex = j;
			}
		}

		isInTree[minIndex] = 1;

		printf("%d %d %d\n", weightArr[minIndex].start, minIndex, weightArr[minIndex].weight);
	}
}
