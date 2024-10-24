#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct TreeNode 
{
	char data;
	int freq;
	TreeNode* left, * right;
	TreeNode(char data, int freq, TreeNode * left = nullptr, TreeNode * right = nullptr)
		: data(data), freq(freq), left(left), right(right) { }
};

struct Obj 
{
	char data;
	int freq;

	Obj(char data = '$', int freq = 0) : data(data), freq(freq) { }

	bool operator()(const Obj& a, const Obj& b) const
	{
		return a.freq > b.freq;
	}
};

void HuffmanCode(TreeNode* node, string code) 
{
	bool hasLeft = false;
	bool hasRight = false;

	if (node->left != nullptr) 
	{
		HuffmanCode(node->left, code + "0");
		hasLeft = true;
	}
	if(node->right != nullptr)
	{
		HuffmanCode(node->right, code + "1");
		hasRight = true;
	}

	if(!hasLeft && !hasRight && node->data != '$')
	{
		cout << node->data << " : " << code << endl;
	}
}

int main() 
{
	int n;
	cin >> n;
	
	vector<Obj> arr(n);

	for (int i = 0; i < n; i++)
	{
		cin >> arr[i].data >> arr[i].freq;
	}

	priority_queue<Obj, vector<Obj>, Obj> pq;

	for (int i = 0; i < n; i++)
	{
		pq.push(arr[i]);
	}

	TreeNode* root = nullptr;
	TreeNode* beforeMerge = nullptr;

	while (pq.size() > 0)
	{
		Obj a = pq.top(); pq.pop();
		
		if (beforeMerge == nullptr && pq.size() > 0) 
		{	
			Obj b = pq.top(); pq.pop();

			TreeNode* left = new TreeNode(a.data, a.freq);
			TreeNode* right = new TreeNode(b.data, b.freq);

			TreeNode* parent = new TreeNode('$', a.freq + b.freq, left, right);

			beforeMerge = parent;
		}
		else if(beforeMerge != nullptr)
		{
			TreeNode* left = nullptr;
			TreeNode* right = nullptr;

			if (beforeMerge->freq > a.freq) 
			{
				left = new TreeNode(a.data, a.freq);
				right = beforeMerge;
			}
			else 
			{
				left = beforeMerge;
				right = new TreeNode(a.data, a.freq);
			}

			TreeNode* parent = new TreeNode('$', a.freq + beforeMerge->freq, left, right);

			beforeMerge = parent;
		}
		else 
		{
			beforeMerge = new TreeNode(a.data, a.freq);
		}

		if (pq.size() == 0) 
		{
			root = beforeMerge;
			break;
		}
	}

	string code = "";

	TreeNode* temp = root;

	HuffmanCode(temp, code);

	return 0;
}
