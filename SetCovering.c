#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // atoi() 사용을 위해 필요
#include <string.h> // strtok() 사용을 위해 필요

int setArr[10000][10000];
int totalSet[10000];

int main() 
{
    char input[100]; // 입력을 저장할 배열
    char* token;     // 분리된 문자열 조각
    int count = 0;   // 추출된 정수 개수

    fgets(input, sizeof(input), stdin); // 한 줄 입력 받기

    // 문자열을 공백을 기준으로 분리
    token = strtok(input, " ");

    while (token != NULL) 
    {
        totalSet[atoi(token)] = 1; // 문자열을 정수로 변환하여 저장
        token = strtok(NULL, " "); // 다음 조각으로 이동
		count++;
    }

	int totalSetCount = count;

    int subSetCount;

	scanf("%d", &subSetCount); // 부분 집합 개수 입력 받기
	getchar();

	int* eachSubSetCount = (int*)malloc(sizeof(int) * (subSetCount + 1));

	for (int i = 0; i <= subSetCount; i++) 
	{
		eachSubSetCount[i] = 0;
	}

	 // 부분 집합 배열 생성
	for (int i = 1; i <= subSetCount; i++)
	{
		fgets(input, sizeof(input), stdin); // 한 줄 입력 받기

		// 문자열을 공백을 기준으로 분리
		token = strtok(input, " ");

		int index = -1;

		while (token != NULL)
		{
			if (index == -1) 
			{
				index = atoi(token);
			}
			else
			{
				setArr[index][atoi(token)] = 1; // 문자열을 정수로 변환하여 저장
				eachSubSetCount[index]++;
			}
			token = strtok(NULL, " "); // 다음 조각으로 이동
		}
	}

	int totalSetCounter = totalSetCount;
	int tempCounter = 0;

	while (totalSetCounter > 0)
	{
		int maxIndex = 0; // 가장 큰 부분 집합의 인덱스
		int max = 0;

		// 가장 큰 부분 집합을 찾기
		for (int i = 1; i <= subSetCount; i++)
		{
			if (eachSubSetCount[i] > max) 
			{
				maxIndex = i;
				max = eachSubSetCount[i];
			}
		}

		for (int i = 1; i <= totalSetCount; i++)
		{
			if (setArr[maxIndex][i] == 1 && totalSet[i])
			{
				totalSet[i] = 0;
				totalSetCounter--;
			}
		}

		for (int i = 1; i <= subSetCount; i++) 
		{
			if (maxIndex == i) continue;

			for (int j = 1; j <= totalSetCount; j++)
			{
				if (setArr[maxIndex][j] && setArr[i][j])
				{
					setArr[i][j] = 0;
					eachSubSetCount[i]--;
				}
			}
		}

		for (int i = 1; i <= totalSetCount; i++) 
		{
			if (setArr[maxIndex][i])
			{
				setArr[maxIndex][i] = 0;
				eachSubSetCount[maxIndex]--;
			}
		}

		printf("%d ", maxIndex);
		tempCounter++;
	}

	printf("\n%d", tempCounter);

	free(eachSubSetCount);

	return 0;
}
