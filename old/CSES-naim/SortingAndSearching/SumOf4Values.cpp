// Sum of Four Values
//
// Problem name: Sum of Four Values
// Problem Link: https://cses.fi/problemset/task/1642
// Author: Bernardo Archegas (https://codeforces.com/profile/Ber)

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define MAXN 100100
#define INF 1000000001
#define pb push_back
#define F first
#define S second
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
const int M = 1e9 + 7;
 
bool comp (int a, int b, int c, int d) {
	bool ber = false;
	ber |= (a == b || a == c || a == d);
	ber |= (b == c || b == d);
	ber |= (c == d);
	return ber;
}
 
int main() { _
    int n, x;
	cin >> n >> x;
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	vector<pair<ll, pii>> w;
	vector<ll> u;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			w.pb({v[i] + v[j], {i, j}});
			u.pb(v[i] + v[j]);
		}
	}	
	sort(w.begin(), w.end());
	sort(u.begin(), u.end());
	int tam = w.size();
	for (int i = 0; i < tam; i++) {
		ll sum = x - w[i].F;
		int pos = lower_bound(u.begin(), u.end(), sum) - u.begin();
		while (pos < tam && (comp(w[i].S.F, w[i].S.S, w[pos].S.F, w[pos].S.S))) pos++;
		if (pos < tam && w[pos].F == sum && !comp(w[i].S.F, w[i].S.S, w[pos].S.F, w[pos].S.S)) {
			cout << w[i].S.F + 1 << ' ' << w[i].S.S + 1 << ' ' << w[pos].S.F + 1 << ' ' << w[pos].S.S + 1 << '\n';
			return 0;
		}
	}
	cout << "IMPOSSIBLE\n";
    return 0;
}