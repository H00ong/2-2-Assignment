#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>

typedef long long L;

typedef struct points
{
	L x;
	L y;
} Point;

double minDistance = 100000000;
Point minPointPair[2];

void ClosestPair(Point * pointSet, int left, int right);
void ThreeMindistance(Point* pointSet, int left, int right);
void TwoMindistance(Point* pointSet, int left, int right);
void ClosestPairBetween(Point* pointSet, int left, int midLeft, int midRight, int right, double minDistance);

int compareX(const void* a, const void* b) 
{
	// 포인터를 Point 구조체 포인터로 형변환
	Point* pointA = (Point*)a;
	Point* pointB = (Point*)b;

	// x좌표 비교
	return pointA->x - pointB->x; // 오름차순 정렬
}

int compareY(const void*a, const void*b) 
{
	// 포인터를 Point 구조체 포인터로 형변환
	Point* pointA = (Point*)a;
	Point* pointB = (Point*)b;

	// y좌표 비교
	return pointA->y - pointB->y; // 오름차순 정렬
}

int main() 
{
	int pointsCount;

	scanf("%d", &pointsCount);

	Point* pointSet
		= (Point*)malloc(sizeof(Point) * pointsCount);

	/*for (int i = 0; i < pointsCount; i++)
		scanf("%lld %lld", &pointSet[i].x, &pointSet[i].y);*/

	char buffer[100];

	getchar();

	for (int i = 0; i < pointsCount; i++) {
		// 입력을 받아 쉼표를 포함한 문자열로 읽기
		fgets(buffer, sizeof(buffer), stdin);

		// sscanf를 사용하여 쉼표를 무시하고 숫자만 읽기
		sscanf(buffer, "%lld , %lld", &pointSet[i].x, &pointSet[i].y);
	}

	qsort(pointSet, pointsCount, sizeof(Point), compareX);

	ClosestPair(pointSet, 0, pointsCount - 1);

	printf("%.6f (%lld, %lld) <-> (%lld, %lld)", minDistance, minPointPair[0].x, minPointPair[0].y, minPointPair[1].x, minPointPair[1].y);

	free(pointSet);
}

void ClosestPair(Point* pointSet, int left, int right) 
{
	if (right - left <= 2)
		ThreeMindistance(pointSet, left, right);
	else
	{
		int rightBound = (left + right) / 2;

		ClosestPair(pointSet, left, rightBound);
		ClosestPair(pointSet, rightBound + 1, right);
		ClosestPairBetween(pointSet, left, rightBound, rightBound + 1, right, minDistance);	
	}
}

void ThreeMindistance(Point * pointSet, int left, int right) 
{
	if (right - left == 2) 
	{
		TwoMindistance(pointSet, left, left + 1);
		TwoMindistance(pointSet, left + 1, right);
		TwoMindistance(pointSet, left, right);
	}
	else
		TwoMindistance(pointSet, left, right);
}

void TwoMindistance(Point* set, int left, int right)
{
	double distance =
		sqrt((set[left].x - set[right].x) * (set[left].x - set[right].x) +
			(set[left].y - set[right].y) * (set[left].y - set[right].y));

	if (distance < minDistance) 
	{
		minDistance = distance;
		minPointPair[0] = set[left];
		minPointPair[1] = set[right];
	}
}


void ClosestPairBetween(Point* pointSet, int left, int midLeft, int midRight, int right, double minDistance) 
{
	double newLeftBoundary = pointSet[midLeft].x - minDistance;
	double newRightBoundary = pointSet[midRight].x + minDistance;

	int newLeftIndex = midLeft;
	int newRightIndex = midRight;

	while (pointSet[newLeftIndex].x > newLeftBoundary && newLeftIndex > left)
		newLeftIndex--;
	while (pointSet[newRightIndex].x < newRightBoundary && newRightIndex < right)
		newRightIndex++;

	int tempCount = newRightIndex - newLeftIndex + 1;
	Point* ySortedSet = (Point*)malloc(sizeof(Point) * (tempCount));
	
	for (int i = 0; i < tempCount; i++)
	{
		ySortedSet[i] = pointSet[newLeftIndex + i];
	}

	// Sort ySortedSet by y-coordinate
	qsort(ySortedSet, tempCount, sizeof(Point), compareY);

	for (int i = 0; i < tempCount; i++) 
	{
		for (int j = i + 1; j < tempCount; j++) 
		{
			if (ySortedSet[j].y - ySortedSet[i].y > minDistance)
				break;

			TwoMindistance(ySortedSet, i, j);
		}
	}

	free(ySortedSet);
}
