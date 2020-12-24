#include <bits/stdc++.h>
using namespace std;




int32_t main(){
	int d , r, t;
	cin >> d >> r >> t;
	for(int i = 4 ; i <= 10000 ; i ++){ // idade da rita
		int rr = (i * (i+1))/2 - 6; // quanto deveria ter
		int tt = 0; // quanto theo deveria ter
		if((i -d) >= 3){
			tt = ((i-d) *(i-d+1))/2 - 3;
		}
		if((rr+tt) == (r + t) && t <= tt){
			cout << r - rr<< endl;
			break;
		}
	}
}