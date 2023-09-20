#include<iostream>
#include<vector>

using namespace std;

int num_conn(vector<bool> &a) {
	int s = 0;
	for (bool e : a) s += e;
	return s;
}

int find(int s, vector<int> &a) {
	while (a[s] != s) {
		s = a[s];
	}
	return s;
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<vector<bool>> v(n + 1, vector<bool>(n + 1, false));

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[a][b] = true;
		v[b][a] = true;
	}

	vector<int> parent(n + 1);
	vector<int> rank(n + 1);

	for (int i = 1; i <= n; i++) parent[i] = i;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (v[i][j]) {
				if (find(i, parent) == find(j, parent)) {
					continue;
				}

				if (rank[i] > rank[j]) {
					parent[j] = i;
				}
				else if (rank[i] < rank[j]) {
					parent[i] = j;  
				}
				else {
					parent[j] = i;
					rank[i]++;
				}
			}
		}
	}

	vector<vector<int>> groups(n + 1, vector<int>());
	for (int i = 1; i <= n; i++) {
		parent[i] = find(i, parent);
		groups[parent[i]].push_back(i);
		if (groups[parent[i]].size() > 3) {
			cout << -1;
			return 0;
		}
	}

	vector<vector<int>> pairs;
	vector<int> singles;
	for (vector<int> &e : groups) {
		if (e.size() == 1) {
			singles.push_back(e[0]);
		}
		else if (e.size() == 2) {
			pairs.push_back(e);
		}
	}
	if (((singles.size() - pairs.size()) % 3) != 0 || (singles.size() < pairs.size())) {
		cout << -1;
		return 0;
	}

	for (vector<int> &e : groups) if (e.size() == 3) {
		cout << e[0] << ' ' << e[1] << ' ' << e[2] << '\n';
	}

	for (vector<int> &e : pairs) {
		cout << e[0] << ' ' << e[1] << ' ' << singles.back() << '\n';
		singles.pop_back();
	}

	for (int i = 0; i < singles.size(); i += 3) {
		cout << singles[i] << ' ' << singles[i + 1] << ' ' << singles[i + 2] << '\n';
	}
}
