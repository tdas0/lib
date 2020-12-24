#include <bits/stdc++.h>
#define pb push_back
#define endl '\n'
#define int long long
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;

struct ret{
 int xi,yi,xf,yf;
 ret(){}
 ret(int a,int b,int c,int d){
 	xi = a;
 	yi = b;
 	xf = c;
 	yf = d;
 }
 void read(){
 	cin>>xi>>yi>>xf>>yf;
 }
 ll area(){
 	return (xf-xi)*(yf-yi);
 }
};

int f=0;

ret inter(ret A,ret B){

	int xi = max(A.xi,B.xi);
	int yi = max(A.yi,B.yi);
	int xf = min(A.xf,B.xf);
	int yf = min(A.yf,B.yf);

	if(xi > xf or yi > yf){
		xi = xf;
		yi = yf;
		f = 1;
	}


	return ret(xi,yi,xf,yf);
}

void solve(){
	ret A,B;
	A.read();
	B.read();
	ll best = max(A.area(),B.area());
	f=0;
	ret C = inter(A,B);

	if(!f){

		best = max(best,(C.xf - C.xi)*(max(A.yf,B.yf) - min(A.yi,B.yi)));
		best = max(best,(C.yf - C.yi)*(max(A.xf,B.xf) - min(A.xi,B.xi)));
	}
	cout << best << endl;

}

int32_t main(){
	fastio;
	int t;
	cin>>t;
	while(t--){
		solve();
	}

}