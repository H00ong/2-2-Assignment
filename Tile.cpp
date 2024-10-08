#include <iostream>

using namespace std;

int num = 0;

bool DrainCheck(int** _arr, int _length, int _x, int _y) {
	for (int i = _x; i < _x + _length; i++) {
		for (int j = _y; j < _y + _length; j++) {
			if (_arr[i][j] != 0) return false;
		}
	}
	return true;

	// 구멍이 있으면 false를 반환
	// 구멍이 없으면 true를 반환
}

void Board(int** _arr, int _arrLength, int _x, int _y) {
	// x와 y는 분할 Board의 좌상단 점
	num++;
	int s = _arrLength / 2;

	if (DrainCheck(_arr, s, _x, _y)) _arr[_x + s - 1][_y + s - 1] = num;
	if (DrainCheck(_arr, s, _x, _y + s)) _arr[_x + s - 1][_y + s] = num;
	if (DrainCheck(_arr, s, _x + s, _y)) _arr[_x + s][_y + s - 1] = num;
	if (DrainCheck(_arr, s, _x + s, _y + s)) _arr[_x + s][_y + s] = num;
	if (_arrLength == 2) return;

	Board(_arr, s, _x, _y);
	Board(_arr, s, _x + s, _y);
	Board(_arr, s, _x, _y + s);
	Board(_arr, s, _x + s, _y + s);
}

int main() 
{
	int n;
	int length;

	int hole_xPos;
	int hole_yPos;

	cin >> n;
	length = 1 << n;
	cin >> hole_yPos >> hole_xPos;

	hole_xPos--;
	hole_yPos--;

	int** arr = new int*[length];
	
	for (int i = 0; i < length; i++) 
	{
		arr[i] = new int[length];
	}

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++) 
		{
			arr[i][j] = 0;
		}
	}

	arr[hole_xPos][hole_yPos] = -1;

	Board(arr, length, 0, 0);

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int i = 0; i < length; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}


