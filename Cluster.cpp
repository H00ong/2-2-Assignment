#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX 1000001

using namespace std;
using pr = pair<int, int>;

bool isInSet[100001];
vector<int> set;
vector<pr> points;
vector<pr> clusters[1001];
vector<pr> clusterCenters;

struct Compare {
	vector<pr> point1; // 기준점 저장

	Compare(const vector<pr>& p) : point1(p) {} // 생성자로 초기화

	bool operator()(const pr& a, const pr& b) const 
	{
		double minDistanceA = MAX;
		double minDistanceB = MAX;

		for (auto point : point1)
		{
			float distanceA = sqrt((point.first - a.first) * (point.first - a.first) + (point.second - a.second) * (point.second - a.second));
			float distanceB = sqrt((point.first - b.first) * (point.first - b.first) + (point.second - b.second) * (point.second - b.second));

			if (minDistanceA > distanceA) 
				minDistanceA = distanceA;

			if (minDistanceB > distanceB) 
				minDistanceB = distanceB;
		}
		if (minDistanceA != minDistanceB)
			return minDistanceA < minDistanceB;
		else 
		{
			if (a.first != b.first)
				return a.first > b.first;
			else
				return a.second > b.second;
		}
	}
};

int main()
{
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < n; i++)
	{
		int a, b;
		cin >> a >> b;
		points.push_back(pr(a, b));
	}

	int count = 1;

	while (count <= k)
	{
		pr chosenPoint;

		if (count == 1)
		{
			chosenPoint = points[0];
		}
		else
		{
			chosenPoint = points[points.size() - 1];
		}
		clusterCenters.push_back(chosenPoint);
		clusters[count].push_back(chosenPoint);
		points.erase(remove(points.begin(), points.end(), chosenPoint), points.end());
		std::stable_sort(points.begin(), points.end(), Compare(clusterCenters));
		count++;
	}

	// 클러스터 중심 선택 후
	for (auto& point : points)
	{
		int closestCluster = -1; // 가장 가까운 클러스터를 저장할 변수
		double minDistance = numeric_limits<double>::max(); // 초기 최소 거리 설정

		for (int i = 0; i < clusterCenters.size(); ++i)
		{
			// 중심점과 현재 점 사이의 거리 계산
			double dx = point.first - clusterCenters[i].first;
			double dy = point.second - clusterCenters[i].second;
			double distance = sqrt(dx * dx + dy * dy);

			// 최소 거리 및 클러스터 업데이트
			if (distance < minDistance)
			{
				minDistance = distance;
				closestCluster = i;
			}
		}

		// 가장 가까운 클러스터에 현재 점 배정
		clusters[closestCluster + 1].push_back(point);
	}

	for (int i = 1; i <= k; i++) 
	{
		pr centerPoint = clusterCenters[i - 1];
		sort(clusters[i].begin(), clusters[i].end(), 
			[](const pr& a, const pr& b) {if (a.first < b.first) return true; 
										  else if (a.first == b.first) return a.second < b.second; 
										  else return false;});

		cout << "group" << i << endl;
		for (auto point : clusters[i])
		{
			cout << point.first << " " << point.second; 
			if (centerPoint == point) 
			{
				cout << "(center)";
			}
			cout << endl;
		}
	}
}
