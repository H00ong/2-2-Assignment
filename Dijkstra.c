#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 10000000

int isInTree[10000];

typedef struct Edge
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
			adj[i][j] = MAX;
		}
	}

	for (int i = 0; i < edgeCount; i++)
	{
		int edge_start, edge_end, weight;
		scanf("%d %d %d", &edge_start, &edge_end, &weight);

		adj[edge_start][edge_end] = weight;
		adj[edge_end][edge_start] = weight;
	}

	for (int i = 1; i < vertexCount; i++)
	{
		weightArr[i].weight = MAX;
		weightArr[i].start = -1;
	}

	int minIndex = 0;
	int min = MAX;
	isInTree[minIndex] = 1;

	for (int i = 1; i < vertexCount - 1; i++) 
	{
		for (int j = 1; j < vertexCount; j++) 
		{
			if (weightArr[minIndex].weight + adj[minIndex][j] < weightArr[j].weight)
			{
				weightArr[j].weight = weightArr[minIndex].weight + adj[minIndex][j];
				weightArr[j].start = minIndex;
			}
		}

		min = MAX;

		for (int j = 1; j < vertexCount; j++) 
		{
			if (!isInTree[j] && weightArr[j].weight < min) 
			{
				min = weightArr[j].weight;
				minIndex = j;
			}
		}

		isInTree[minIndex] = 1;
	}

	for (int i =1; i < vertexCount; i++)
	{
		printf("%d %d\n", i, weightArr[i].weight);
	}
}
