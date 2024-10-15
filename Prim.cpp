#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using pr = pair<int, int>;
using tp = tuple<int, int, int>;

bool isMST[10001];
vector<pr> adj[10001];
vector<tp> result;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, e;
	cin >> n >> e;
	while (e--) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
		adj[v].push_back({ w, u });
	}

	int st = 0, cnt = 0;
	isMST[st] = true;
	priority_queue<tp, vector<tp>, greater<tp>> pq;
	
	for (auto nb : adj[st]) {
		pq.push(make_tuple(nb.first, st, nb.second));
	}

	while (cnt < n - 1) {
		int cost, a, b;
		tie(cost, a, b) = pq.top(); pq.pop();

		if (isMST[b]) continue;

		isMST[b] = true;

		cout << a << " " << b << " " << cost << endl;

		cnt++;

		for (auto nb : adj[b]) {
			if (!isMST[nb.second]) {
				pq.push(make_tuple(nb.first, b, nb.second));
			}
		}
	}

	return 0;
}