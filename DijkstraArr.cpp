#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
using pr = pair<int, int>;

vector<pr> adj[10000];
pr result[10000];
bool isInTree[10000];

int main() 
{
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

	int count = 0;

	
	result[0].first = 0;
	result[0].second = -1;
	
	for (int i = 1; i < vertexCount; i++) 
	{
		result[i].first = INT32_MAX;
		result[i].second = -1;
	}
	
	int beforeIndex = 0;
	
	isInTree[beforeIndex] = true;

	while (count < vertexCount - 1) 
	{
		for (auto elem : adj[beforeIndex]) 
		{
			if (!isInTree[elem.second] && 
				(result[elem.second].first == INT32_MAX || result[elem.second].first > result[beforeIndex].first + elem.first))
			{
				result[elem.second].first = result[beforeIndex].first + elem.first;
				result[elem.second].second = beforeIndex;
			}
		}

		int min = INT32_MAX;

		for (int i = 1; i < vertexCount; i++) 
		{
			if (isInTree[i]) continue;

			if (min > result[i].first) 
			{
				beforeIndex = i;
				min = result[i].first;
			}
		}

		isInTree[beforeIndex] = true;
		count++;
	}

	for (int i = 1; i < vertexCount; i++) 
	{
		cout << i << " " << result[i].first << endl;
	}

	return 0;
}
