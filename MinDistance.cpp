#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <stdlib.h>

using namespace std;

typedef long long L;
double minDistance = numeric_limits<double>::max();

void ClosestDistance(vector < pair<L, L>> &_pointsVec, int _left, int _right);
void ThreeOrTwoPointsMinDistance(vector<pair<L, L>>& _pointsVec, int _left, int _right);
void TwoPointsMinDistance(const pair<L, L>& a, const pair<L, L>& b);
void ClosestBetweenDistance(vector<pair<L, L>>& _pointsVec, int _left, int _SLRightBound, int _SRLeftBound, int _right, float _currentMinDistance);


void ClosestDistance(vector<pair<L, L>> &_pointsVec, int _left, int _right) 
{
	if (_right - _left <= 2) 
	{
		ThreeOrTwoPointsMinDistance(_pointsVec, _left, _right);
	}
	else 
	{
		int rightBound = (_right - _left + 1) % 2 == 0 ? _left + (_right - _left + 1) / 2 - 1: _left + (_right - _left + 1) / 2;

		ClosestDistance(_pointsVec, _left, rightBound);
		ClosestDistance(_pointsVec, rightBound + 1, _right);
		ClosestBetweenDistance(_pointsVec, _left, rightBound, rightBound + 1, _right, minDistance);
	}
}

void ThreeOrTwoPointsMinDistance(vector<pair<L, L>>& _pointsVec, int _left, int _right)
{
	if (_right - _left <= 1)
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_right]);
	else 
	{
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_left + 1]);
		TwoPointsMinDistance(_pointsVec[_left + 1], _pointsVec[_right]);
		TwoPointsMinDistance(_pointsVec[_left], _pointsVec[_right]);
	}
}

void TwoPointsMinDistance(const pair<L, L> &a, const pair<L , L> &b)
{
	double distance = sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));

	if (distance < minDistance)
		minDistance = distance;
}

void ClosestBetweenDistance(vector<pair<L, L>>& _pointsVec, int _left, int _SLRightBound, int _SRLeftBound, int _right, float _currentMinDistance)
{
	float _leftBoundaryVal = _pointsVec[_SLRightBound].first - _currentMinDistance;
	float _rightBoundaryVal = _pointsVec[_SRLeftBound].first + _currentMinDistance;

	int _leftBoundIndex = _SLRightBound;
	int _rightBoundIndex = _SRLeftBound;

	while (_pointsVec[_leftBoundIndex].first >= _leftBoundaryVal && _leftBoundIndex > 0)
		_leftBoundIndex--;
	while (_pointsVec[_rightBoundIndex].first <= _rightBoundaryVal && _rightBoundIndex < _right)
		_rightBoundIndex++;

	vector<pair<L, L>> SLySortingVec(_pointsVec.begin() + _leftBoundIndex, _pointsVec.begin() + _SLRightBound + 1);
	sort(SLySortingVec.begin(), SLySortingVec.end(), 
		[](const pair<L, L>& a, const pair<L, L>& b) { return a.second < b.second;});

	vector<pair<L, L>> SRySortingVec(_pointsVec.begin() + _SRLeftBound, _pointsVec.begin() + _rightBoundIndex + 1);
	sort(SRySortingVec.begin(), SRySortingVec.end(),
		[](const pair<L, L>& a, const pair<L, L>& b) { return a.second < b.second;});

	for (int i = 0; i < SLySortingVec.size(); i++) 
	{
		for (int j = 0; j < SRySortingVec.size(); j++) 
		{
			if (abs(SRySortingVec[j].second - SLySortingVec[i].second) >= minDistance)
				break;
			TwoPointsMinDistance(SRySortingVec[j], SLySortingVec[i]);
		}
	}
}

int main() 
{
	int numberOfPoints;

	cin >> numberOfPoints;
	cin.ignore();

	vector<pair<L, L>> pointsVec;

	string input;
	
	for (int i = 0; i < numberOfPoints; i++) 
	{
		getline(cin, input);
		input.erase(std::remove(input.begin(), input.end(), ','), input.end());
		stringstream ss(input);
		
		L x, y;
		ss >> x >> y;

		pointsVec.push_back(pair<L, L>(x, y));
;	}

	sort(pointsVec.begin(), pointsVec.end(),
		[](const pair<L, L>& a, const pair<L, L>& b) { return a.first < b.first;});

	ClosestDistance(pointsVec, 0, pointsVec.size() - 1);

	printf("%.6f", minDistance);
}


