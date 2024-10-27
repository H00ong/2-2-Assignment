#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct TreeNode 
{
	char data;
	int freq;
	TreeNode* left, * right;
	TreeNode(char data = 0, int freq = 0, TreeNode * left = nullptr, TreeNode * right = nullptr)
		: data(data), freq(freq), left(left), right(right) { }

	bool operator()(const TreeNode* a, const TreeNode* b) const
	{
		return a->freq > b->freq;
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
	
	vector<TreeNode *> arr(n);

	for (int i = 0; i < n; i++)
	{
		arr[i] = new TreeNode();
		cin >> arr[i]->data >> arr[i]->freq;
	}

	priority_queue<TreeNode*, vector<TreeNode*>, TreeNode> pq;

	for (int i = 0; i < n; i++)
	{
		pq.push(arr[i]);
	}


	while (pq.size() > 1)
	{
		TreeNode* left = pq.top(); pq.pop();
		TreeNode* right = pq.top(); pq.pop();

		TreeNode* newNode = new TreeNode('$', left->freq + right->freq, left, right);

		pq.push(newNode);
	}

	TreeNode* root = pq.top(); pq.pop();

	HuffmanCode(root, "");

	for (auto elem : arr)
	{
		delete elem;
	}

	return 0;
}
