#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;
using pr = pair<int, int>;

vector<pr> adj[10000];
int result[10000];
bool isInTree[10000];

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int vertexCount, edgeCount;

	cin >> vertexCount >> edgeCount;

	while (edgeCount--) {
		int edge_start, edge_end, weight;
		cin >> edge_start >> edge_end >> weight;
		adj[edge_start].push_back({ weight, edge_end });
		adj[edge_end].push_back({ weight, edge_start });
	}

	int count = 0;
	isInTree[0] = true;
	priority_queue<pr, vector<pr>, greater<pr>> pq;

	for (auto elem : adj[0]) 
		pq.push(make_pair(elem.first, elem.second));

	while (count < vertexCount - 1) 
	{
		auto var = pq.top(); pq.pop();

		if (isInTree[var.second]) continue;

		isInTree[var.second] = true;

		count++;

		result[var.second] = var.first;

		for (auto elem : adj[var.second])
		{
			if (!isInTree[elem.second])
			{
				pq.push(make_pair(elem.first + var.first, elem.second));
			}
		}
	}

	for (int i = 1; i < vertexCount; i++) 
	{
		cout << i << " " << result[i] << endl;
	}

	return 0;
}
