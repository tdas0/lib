#include <bits/stdc++.h>
using namespace std;



int32_t main(){
	vector<int> v(3);
	for(int i = 0 ; i< 3 ; i ++) cin >> v[i];
	vector<int> x(2);
	for(int i = 0 ; i < 2 ; i ++) cin >> x[i];
	sort(v.begin() , v.end());
	bool can = false;
	do{
		sort(x.begin() , x.end());
		do{
			int L = v[1]*2 + v[2] * 2;
			int R = v[0] + v[2]* 2; 
			int L1 = v[2] + v[0];
			int R1 = v[1] + v[0] + v[1] + v[2] + v[1];
			if(L <= x[0] && R <= x[1]) can = true;
			if(L1 <= x[0] && R1 <= x[1]) can = true;
			
		} while(next_permutation(x.begin() , x.end())) ; 
	} while(next_permutation(v.begin() , v.end()));
	if(can) cout <<"Yes" << endl;
	else cout <<"No" << endl;
}