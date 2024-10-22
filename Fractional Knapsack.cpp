#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
	int index;
	int weight;
	int value;
	double unitValue;
};

int main() 
{
	int itemCount; double totalCapacity;
	
	cin >> itemCount;

	vector<Item> items(itemCount);

	for (int i = 0; i < itemCount; i++) 
	{
		cin >> items[i].weight >> items[i].value;
		items[i].index = i;
		items[i].unitValue = (double)items[i].value / items[i].weight;
	}

	cin >> totalCapacity;

	sort(items.begin(), items.end(), [](const Item& a, const Item& b) {return a.unitValue > b.unitValue;});

	double weigthSum = 0;
	double valueSum = 0;

	for (int i = 0; weigthSum < totalCapacity && i < itemCount; i++) 
	{
		if(weigthSum + items[i].weight <= totalCapacity)
		{
			weigthSum += items[i].weight;
			valueSum += items[i].value;
			printf("%d %.1f\n", items[i].index, 1.0f);
		}
		else 
		{
			double temp = totalCapacity - weigthSum;
			double ratio = temp / items[i].weight;

			valueSum += items[i].value * ratio;
			printf("%d %.1f\n", items[i].index, ratio);
			break;
		}
	}

	printf("%.0f", valueSum);
}
