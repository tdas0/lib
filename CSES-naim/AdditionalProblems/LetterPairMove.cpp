/*
n-1 A e B's
AB..BA -> todos A's depois B's
*/
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector<string> sol;
	int n;
	string s;
	cin >> n >> s;
	auto go = [&](int i, int j) {
		swap(s[i], s[j]);
		swap(s[i + 1], s[j + 1]);
		sol.emplace_back(s);
	};
	for (int i = 0; i < n - 1; )
		if (s[i] == 'A')
			++i;
		else if (s[i] == '.') {
			int j = i + 2;
			while (j < 2 * n - 1 && s[j] != 'A')
				++j;
			if (j == 2 * n - 1)
				if (n < 4) {
					cout << -1;
					return 0;
				}
				else {
					go(2 * n - 2, n - 2);
					go(n, 2 * n - 2);
					continue;
				}
			go(i, j);
		}
		else if (s[i + 1] == '.')
			go(i + 1, i + 3);
		else {
			int j = i;
			while (s[j] != '.')
				++j;
			go(i, j);
		}
	cout << sol.size() << '\n';
	for (const auto& x : sol)
		cout << x << '\n';
}
