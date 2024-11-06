#include <iostream>
#include <vector>
#define MAX 1000000
using namespace std;

int arr[100][100];
int arr2[100][100];

void PrintMatrix(int start, int end)
{
	if (start == end)
	{
		cout << "M" << start + 1; // 시작점과 끝점이 같으면 괄호 없이 출력
	}
	else
	{
		// 시작점과 끝점이 다르면 괄호 출력
		cout << "(";
		PrintMatrix(start, arr2[start][end]); // 시작점부터 중간점까지 출력
		PrintMatrix(arr2[start][end] + 1, end); // 중간점부터 끝점까지 출력
		cout << ")";
	}

}

int main()
{
	int n;

	cin >> n;

	vector<pair<int, int>> matrix(n);

	for (int i = 0; i < n; i++)
	{
		cin >> matrix[i].first;
		cin >> matrix[i].second;
	}

	// table에서 대각선 방향의 값들을 채우는 과정
	for (int d = 1; d < n; d++) // d는 대각선 시작점을 의미
	{
		for (int i = 0; i < n - d; i++) // 연산 시작점 인덱스
		{
			int  j = i + d; // 연산 끝점 끝점이 n - 1까지만 가능하므로 i가 n - d - 1까지만 가능한 것
			arr[i][j] = MAX; // 대입 연산을 수행할 것이므로 최대값으로 초기화
			for (int k = i; k < j; k++) // k는 연산 경유점
			{
				if (arr[i][k] + arr[k + 1][j] + matrix[i].first * matrix[k].second * matrix[j].second < arr[i][j])
				{
					// 연산 경유점을 거쳐서 가는게 더 빠르면
					arr[i][j] = arr[i][k] + arr[k + 1][j] + matrix[i].first * matrix[k].second * matrix[j].second; 
					arr2[i][j] = k; // 연산 중간점 저장
				}
			}
		}
	}

	cout << arr[0][n - 1] << endl;
	PrintMatrix(0, n - 1);
}
