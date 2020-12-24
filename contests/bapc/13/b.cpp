#include <bits/stdc++.h>
using namespace std;
int n , c, m;
int b[30];
double p[30];
double dp[1<<17][17] ;
int cz = 0 , cost[1<<17];
bool vis[1<<17][17];




int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
while(t--){
	cin >> n >> c >> m;
	for(int i = 0 ; i < n; i++){
		cin >> b[i];
		int x;
		cin >> x;
		p[i] =( x * 1.0) / 100.0;
	}
	for(int i = 0 ; i < (1<<n) ; i ++){
		cost[i] = 0;
		for(int j = 0 ; j <n ; j ++){
			if((1<<j) & i) cost[i] += b[j];
		}
		for(int j =0  ; j <= c; j ++) dp[i][j] = 0.000;
		if(cost[i] <= m){
			dp[i][c] = 1.000;
		}
	}
	for(int j = ((1<<n) - 1) ; j >= 0 ; j --){
		for(int k = c - 1; k >= 0 ; k --){
			for(int i = 0 ; i < n; i++){
				if(!((1<<i) & j)){
					dp[j][k] = max(dp[j][k] , dp[j^(1<<i)][k+1]*p[i] + dp[j^(1<<i)][k]*(1.0 - p[i]));
				}
			}
		}
	}
	cout << fixed << setprecision(9) << dp[0][0] << endl;
}
}