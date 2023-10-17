/**
 * Author: Emanuel (UFMG)
 * License: CC0
 * Description: Match every element from A to B so that there is no pair x \in A
 * and y \in B and x not paired with y s.t. y prefers x and x prefers y.
 * a[i] has the elements of Bsorted by preference of i,
 * b[j] elements of A sorted by preference of j. |A| <= |B|.
 * Retorna um vetor v de tamanho |A| onde v[i] guarda o match de i
 * Status: Tested on 
 * Complexity: $O(|A||B|)$
 */

vector<int> stable_marriage(vector<vector<int>> &a, vector<vector<int>> &b) {
	int n = a.size(), m = b.size();
	assert(a[0].size() == m and b[0].size() == n and n <= m);
	vector<int> match(m, -1), it(n, 0);
	vector inv_b(m, vector<int>(n));
	for (int i = 0; i < m; i++) for (int j = 0; j < n; j++)
		inv_b[i][b[i][j]] = j;

	queue<int> q;
	for (int i = 0; i < n; i++) q.push(i);
	while (q.size()) {
		int i = q.front(); q.pop();
		int j = a[i][it[i]];

		if (match[j] == -1) match[j] = i;
		else if (inv_b[j][i] < inv_b[j][match[j]]) {
			q.emplace(match[j]);
			it[match[j]]++;
			match[j] = i;
		} else q.emplace(i), it[i]++;
	}

	vector<int> ret(n);
	for (int i = 0; i < m; i++) if (match[i] != -1) ret[match[i]] = i;
	return ret;
}