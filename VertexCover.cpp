#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
using pr = pair<int, int>;

std::set<int> pointSet;
vector<pr> vertex;

int main() 
{
	int n;
	cin >> n;
	
	int temp;

	for (int i = 0; i < n; i++) 
	{
		int  a, b;
		cin >> a >> b;
		if (a > b) swap(a, b);
		vertex.push_back(pr(a, b));
	}

	sort(vertex.begin(), vertex.end(), [](const pr& a, const pr& b)
		{
			int sum1 = a.first + a.second;
			int sum2 = b.first + b.second;
			return sum1 == sum2 ? a < b : sum1 < sum2;
		});
	
	while (!vertex.empty())
	{
		pr chosenVertex;

		if(vertex.size() == n)
			chosenVertex = pr(0, 1);
		else
			chosenVertex = vertex[0];

		for (auto iter = vertex.begin(); iter != vertex.end();)
		{
			if (iter->first == chosenVertex.first || iter->first == chosenVertex.second ||
				iter->second == chosenVertex.first || iter->second == chosenVertex.second)
			{
				iter = vertex.erase(iter);
			}
			else
			{
				iter++;	
			}
		}
		pointSet.insert(chosenVertex.first);
		pointSet.insert(chosenVertex.second);
	}
	// {0, 1, 2, 3}
	cout << "{";
	for (auto it = pointSet.begin(); it != pointSet.end(); ++it)
	{
		if (it != pointSet.begin()) cout << ", ";
		cout << *it;
	}
	cout << "}" << endl;

	return 0;
}
