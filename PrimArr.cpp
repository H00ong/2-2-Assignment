#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;
using pr = pair<int, int>;
using tp = tuple<int, int, int>;

bool isInTree[10000];
vector<pr> adj[10000];
pr weightArr[10000];

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int vertexCount, edgeCount;
	
	cin >> vertexCount >> edgeCount;

	while (edgeCount--) 
	{
		int edge_start, edge_end, weight;
		cin >> edge_start >> edge_end >> weight;
		adj[edge_start].push_back({ weight, edge_end });
		adj[edge_end].push_back({ weight, edge_start });
	}

	for(int i = 0; i < vertexCount; i++)
	{
		weightArr[i].first = INT32_MAX;
		weightArr[i].second = -1;
	}
	
	isInTree[0] = true;
	int count = 0;
	
	int minIndex = 0;
	int temp = vertexCount - 1;

	while (temp--) 
	{
		for (auto elem : adj[minIndex])
		{
			if (weightArr[elem.second].first > elem.first)
			{
				weightArr[elem.second].first = elem.first;
				weightArr[elem.second].second = minIndex;
			}
		}
		
		minIndex = 0;

		int beforeMin = INT32_MAX;

		for (int i = 0; i < vertexCount; i++)
		{
			if (weightArr[i].first < beforeMin && !isInTree[i]) 
			{
				minIndex = i;
				beforeMin = weightArr[i].first;
			}
		}

		isInTree[minIndex] = true;

		cout << weightArr[minIndex].second << " " << minIndex << " " << weightArr[minIndex].first << endl;
	}

	return 0;
}
