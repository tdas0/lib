#include <bits/stdc++.h>
using namespace std;



int32_t main(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		double p , c;
		cin >> p >> c;
		p /= 100.00;
		c /= 100.00;
		double ans = (p) / (c+1.00);
		cout << fixed << setprecision(7) << ans * 100.00 << endl;
	}
}
