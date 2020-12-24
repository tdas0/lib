/*
* Description: retora o lower e upper hull. Bom para fazer busca ternaria
* ** Based on hacker earth blog
* Status: somewhat tested
* Melhor colocar um split hull no lugar...
*/
#include "Point.h"

typedef Point<ll> P;
typedef pair<vector<P>,vector<P>> vp;
vp convexHull(vector<P> pts) {
	int n = pts.size();
	sort(pts.begin(),pts.end());
	vector<P> H1(2*n),H2(2*n),H(2*n);
	// build lower
	int k=0;
	rep(i,0,n){
		while(k>=2 && H[k-2].cross(H[k-1],pts[i])<=0)k--;
		H[k++] = pts[i];
	}
	H1 = H;
	H1.resize(k);
	 k=0;
   // upper hull
	for(int i=n-2;i>=0;i--){
		while(k>=2 && H[k-2].cross(H[k-1],pts[i])<=0)k--;
		H[k++] = pts[i];
	}
	H2 = H;
	H2.resize(k);
	return vp(H1,H2); 
}
