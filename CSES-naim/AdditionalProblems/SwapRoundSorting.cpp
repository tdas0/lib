// em uma etapa pode swap em qualquer quantidade de pares sem inters.
// quer ordenar
// O(N)
#include <bits/stdc++.h>
using namespace std;
 
stringstream ss;
 
bool solve(int n, vector<int> &a, int f) {
	vector<pair<int, int>> ans;
 
	vector<bool> vis(n+1);
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			vector<int> p;
			int cur = i;
			while (!vis[cur]) {
				vis[cur] = 1;
				p.push_back(cur);
				cur = a[cur];
			}
 
			if (f) {
				for (int j = 1; j < p.size(); j += 2) {
					ans.emplace_back(p[j-1], p[j]);
				}
			} else {
				for (int j = 1, k = p.size() - 1; j < k; j++, k--) {
					ans.emplace_back(p[j], p[k]);
				}
			}
		}
	}
	if (ans.empty()) return 0;
 
	ss << ans.size() << '\n';
	for (auto [x, y]: ans) {
		ss << x << ' ' << y << '\n';
		swap(a[x], a[y]);
	}
 
	return 1;
}
 
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
 
	int n; cin >> n;
	vector<int> a(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
 
	cout << (solve(n, a, 0) + solve(n, a, 1)) << '\n';
	cout << ss.str();
 
	return 0;
}
