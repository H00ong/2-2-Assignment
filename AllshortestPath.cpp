#include <iostream>

int arr[100][100]; // 가중치를 저장할 배열

using namespace std;

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j]; // table 입력받기 -> 경로에 대한 가중치 입력 받음
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
			if (k == i) continue; // 경유지와 출발지가 같으면 continue
            for (int j = 0; j < n; j++)
            {
				if (k == j || i == j) continue; // 경유지와 도착지가 같으면 continue
                if ((arr[i][j] > arr[i][k] + arr[k][j] || arr[i][j] == -1)
					&& arr[i][k] > 0 && arr[k][j] > 0) // 경유지를 거쳐서 가는게 더 빠르면
                {
					arr[i][j] = arr[i][k] + arr[k][j]; // 가중치 갱신
                }
            }
        }
    }
	// 출력
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j < n - 1)
                cout << arr[i][j] << " ";
            else
                cout << arr[i][j] << endl;
        }
    }
}
