#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

using L = long long;
using PL = pair<L, L>;
double minDistance = numeric_limits<double>::max(); // minDistance는 float 최대 값 부여

vector<PL> ysortedVec; // 시간 복잡도를 nlogn으로 바꾸는 알고리즘

void ClosestDistance(vector < PL> &_pointsVec, int _left, int _right);
void ThreeOrTwoPointsMinDistance(vector<PL>& _pointsVec, int _left, int _right);
void TwoPointsMinDistance(const PL& a, const PL& b);
void ClosestBetweenDistance(vector<PL>& _pointsVec, int _left, int _SLRightBound, int _SRLeftBound, int _right, float _currentMinDistance);

void ClosestDistance(vector<PL> &_pointsVec, int _left, int _right) 
{
	if (_right - _left <= 2) 
	{
		ThreeOrTwoPointsMinDistance(_pointsVec, _left, _right); // 점의 개수가 3개 이하면 minDistance 비교
	}
	else 
	{
		int rightBound = (_right - _left + 1) % 2 == 0 ? _left + (_right - _left + 1) / 2 - 1: _left + (_right - _left + 1) / 2; // 홀수 개일 때 left가 항상 1개 더 많이 갖도록 설정

		ClosestDistance(_pointsVec, _left, rightBound); // 분할 정복 left
		ClosestDistance(_pointsVec, rightBound + 1, _right); // 분할 정복 right
		ClosestBetweenDistance(_pointsVec, _left, rightBound, rightBound + 1, _right, minDistance); // Merge -> left - right 사이의 점들 사이에서 minDistance 비교
	}
}

void ThreeOrTwoPointsMinDistance(vector<PL>& _pointsVec, int _left, int _right)
{
	// 3개 이하의 점에서 minDistance와 비교
	if (_right - _left <= 1)
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_right]);
	else 
	{
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_left + 1]);
		TwoPointsMinDistance(_pointsVec[_left + 1], _pointsVec[_right]);
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_right]);
	}
}

void TwoPointsMinDistance(const PL &a, const pair<L , L> &b)
{
	double distance = sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));

	if (distance < minDistance)
		minDistance = distance;
}

void ClosestBetweenDistance(vector<PL>& _pointsVec, int _left, int _SLRightBound, int _SRLeftBound, int _right, float _currentMinDistance)
{
	// SLRightBound에 해당하는 x값 - minDistance를 leftBoundaryVal로 설정하고 이 값보다 큰 x값을 가진 점을 새로운 왼쪽 기준점으로 설정한다.
	// SRleftBound에 해당하는 x값 + minDistance를 leftBoundaryVal로 설정하고 이 값보다 작은 값을 가진 점을 새로운 오른쪽 기준점으로 설정한다.
	float _leftBoundaryVal = _pointsVec[_SLRightBound].first - _currentMinDistance; 
	float _rightBoundaryVal = _pointsVec[_SRLeftBound].first + _currentMinDistance;

	vector<PL> yBetweenVec;

	for (int i = 0; i < ysortedVec.size(); i++)
	{
		if (ysortedVec[i].first >= _leftBoundaryVal && ysortedVec[i].first <= _rightBoundaryVal)
			yBetweenVec.push_back(ysortedVec[i]);
	}

	for (int i = 0; i < yBetweenVec.size(); i++)
	{
		for (int j = i + 1; j < yBetweenVec.size(); j++)
		{
			// y-좌표 차이가 minDistance 이상이면 비교 종료
			if ((yBetweenVec[j].second - yBetweenVec[i].second) >= minDistance)
				break; // 조기 종료

			// 두 점 간의 거리 계산
			TwoPointsMinDistance(yBetweenVec[j], yBetweenVec[i]);
		}
	}
}

int main() 
{
	int numberOfPoints;

	cin >> numberOfPoints;
	cin.ignore();

	vector<PL> pointsVec; // x, y값을 갖도록 pair를 기준으로 한 벡터를 사용
	
	string input;
	
	for (int i = 0; i < numberOfPoints; i++) 
	{
		getline(cin, input);
		input.erase(std::remove(input.begin(), input.end(), ','), input.end());
		stringstream ss(input);
		
		L x, y;
		ss >> x >> y;

		pointsVec.push_back(PL(x, y));
		ysortedVec.push_back(PL(x, y));
;	}

	sort(pointsVec.begin(), pointsVec.end());
	sort(ysortedVec.begin(), ysortedVec.end(), [](const PL& a, const PL& b) {return a.second < b.second;});

	ClosestDistance(pointsVec, 0, pointsVec.size() - 1);

	printf("%.6f", minDistance);
}
