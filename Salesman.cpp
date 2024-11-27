#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000001

using namespace std;
using pr = pair<int, int>;

int arr[1001][1001];
bool visited[1001];
vector<pr> adj[10001];
vector<pr> path;
pr weight[10001];

int main() 
{
	int n;

	cin >> n;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++)
		{
			if (arr[i][j] != 0)
			{
				adj[i].push_back({ arr[i][j], j });
				adj[j].push_back({ arr[i][j], i });
			}
		}
	}

	visited[0] = true;

	for (int i = 0; i < n; i++)
	{
		weight[i].first = MAX;
		weight[i].second = -1;
	}
	
	int count = 0;
	int minIndex = 0;

	for (int count = 0; count < n - 1; count++) 
	{
		for (auto elem : adj[minIndex])
		{
			if (weight[elem.second].first > elem.first)
			{
				weight[elem.second].first = elem.first;
				weight[elem.second].second = minIndex;
			}
		}

		int beforeMin = MAX;

		for (int i = 0; i < n; i++)
		{
			if (weight[i].first < beforeMin && !visited[i])
			{
				minIndex = i;
				beforeMin = weight[i].first;
			}
		}

		visited[minIndex] = true;

		path.push_back(pr(weight[minIndex].second, minIndex));
	}

	// MST: (0, 3) (3, 2) (0, 1) 
	// 방문 경로: 0 3 2 1 0

	for (int i = 0; i < n - 1; i++) 
	{
		if (i == 0) cout << "MST: ";
		cout << "(" << path[i].first << ", " << path[i].second << ") ";
	}
	cout << endl;

	cout << "방문 경로: 0 ";
	for (int i = 0; i < n; i++)
	{
		if (i == n - 1) 
			cout << "0" << endl;
		else 
			cout << path[i].second << " ";
	}
}
