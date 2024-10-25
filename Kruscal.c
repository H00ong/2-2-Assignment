#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int from, to, weight;
} Edge;

int parent[10000];

int GetParent(int x) 
{
	if (parent[x] == x) return x;
	return parent[x] = GetParent(parent[x]);	
}

int UnionParent(int a, int b)
{
	a = GetParent(a);
	b = GetParent(b);

	parent[a] = b;
}

int CompareEdge(const void* a, const void* b)
{
	Edge* edgeA = (Edge*)a;
	Edge* edgeB = (Edge*)b;

	return edgeA->weight > edgeB->weight;
}

int main() 
{
	int vertexCount, edgeCount;

	scanf("%d %d", &vertexCount, &edgeCount);

	Edge* edge = (Edge*)malloc(sizeof(Edge) * edgeCount);

	for (int i = 0; i < edgeCount; i++)
		scanf("%d %d %d", &edge[i].from, &edge[i].to, &edge[i].weight);

	qsort(edge, edgeCount, sizeof(Edge), CompareEdge);

	for (int i = 0; i < vertexCount; i++)
		parent[i] = i;

	int weightSum = 0;

	for (int i = 0; i < vertexCount; i++)
	{
		int from = edge[i].from;
		int to = edge[i].to;

		if (GetParent(from) == GetParent(to)) continue;

		UnionParent(from, to);

		weightSum += edge[i].weight;

		printf("%d %d %d\n", from, to, edge[i].weight);
	}

	printf("%d", weightSum);
}
