#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    // 전체 집합 입력 받기
    string input;
    getline(cin, input);

    istringstream iss(input);

    vector<int> totalSet;
    
    int temp;

    while (iss >> temp) 
    {
        totalSet.push_back(temp);
    }

    // 부분 집합 개수 입력 받기
    int subSetCount;
    cin >> subSetCount;
    cin.ignore(); // 개행 문자 처리

    // 부분 집합 배열 생성
    vector<vector<int>> arr(subSetCount + 1);

    // 부분 집합 입력받기
    for (int i = 1; i <= subSetCount; i++) 
    {
        getline(cin, input);

        istringstream iss(input);

        int temp2 = -1;

        while (iss >> temp) 
        {
            if (temp2 == -1) 
            {
                temp2 = 0;
                continue;
            }
            arr[i].push_back(temp);
        }
    }

    int setCount = 0;

    while (!totalSet.empty()) {
        int maxIndex = 1;

        // 가장 큰 부분 집합을 찾기
        for (int i = 1; i <= subSetCount; i++) 
        {
            if (arr[i].size() > arr[maxIndex].size())
                maxIndex = i;
        }

        set<int> newSet(arr[maxIndex].begin(), arr[maxIndex].end());
        arr[maxIndex].clear();

        //totalSet.erase(remove_if(totalSet.begin(), totalSet.end(), [&](int x) {
        //    return newSet.find(x) != newSet.end();
        //    }), totalSet.end());

        for (auto it = totalSet.begin(); it != totalSet.end(); )
        {
            if (newSet.find(*it) != newSet.end())
				it = totalSet.erase(it);
            else
                ++it; // 삭제하지 않으면 다음 요소로 이동
        }

        for (int i = 1; i <= subSetCount; i++) 
        {
            if (i == maxIndex) continue;

			for (auto it = arr[i].begin(); it != arr[i].end(); )
			{
				if (newSet.find(*it) != newSet.end())
					it = arr[i].erase(it);
				else
					++it;
			}
        }

        std::cout << maxIndex << " ";
        setCount++;
    }

    std::cout << endl;
    std::cout << setCount;

    return 0;
}
