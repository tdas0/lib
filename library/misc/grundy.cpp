#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int g[101][101];
bool vis[101][101];
int solve(int i , int j){
	if(vis[i][j]) return g[i][j];
	vis[i][j] = true;
	if(i == 1 && j ==2 ) return g[i][j] = 0;
	if(j == 1 && i ==2 ) return g[i][j] = 0; 
	bitset<303> mex;
	mex.set();
	for(int u = 1 ; u < i ; u++){
		if(i-u != j)
		mex[solve(i-u,j)]=0;
	}
	for(int u = 1 ; u < j ; u++){
		if(j-u != i)
		mex[solve(i,j-u)]=0;
	}
	for(int u = 1; u < min(i,j) ; u++){
		if(i-u != j-u)
		mex[solve(i-u,j-u)]=0;
	}
	return g[i][j] = mex._Find_first();
}
 
int32_t main(){
	int n;
	cin>>n;
	bool jafoi = false;
	int X = 0;
	for(int i = 0 ; i < n ; i ++){
		int x , y;
		cin>>x>>y;
		if(x == 0 || y == 0) jafoi = true;
		else if(x == y) jafoi = true;
		else X ^= solve(x,y);
	}
	if(jafoi) cout<<"Y"<<endl;
	else{
		if(X != 0) cout<<"Y"<<endl;
		else cout<<"N"<<endl;
	}
}
