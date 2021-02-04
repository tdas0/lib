#include <bits/stdc++.h>
using namespace std;
const int N = 5005;
typedef long long ll;
int dp[N][N] , a[N] , b[N] , n;



int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d" , &a[i] , &b[i]);
	}
	for(int i = 0 ; i <= n; i ++){
		for(int j = 0 ; j <= i ; j ++){
			dp[i][j] = (int) 1e9;
		}
	}
	int ans = n;
	dp[0][0] = 0;
	for(int i = 0 ; i <= n; i ++){
		for(int j = 0 ; j <= i ; j ++){
			if(dp[i][j] >= (int) 1e9)
				continue;
			if(i == n){
				ans = min(ans, j);
				continue;
			}
			if(i * a[i+1] >= dp[i][j] || i == 0){
				dp[i+1][j] = min(dp[i+1][j] , dp[i][j] + a[i+1]);
			}
			else{
				dp[i+1][j+1] = min(dp[i+1][j+1] , dp[i][j] + a[i+1]);
			}
			if(i * b[i+1] >= dp[i][j] || i == 0){
				dp[i+1][j] = min(dp[i+1][j] , dp[i][j] + b[i+1]);
			}
			else{
				dp[i+1][j+1] = min(dp[i+1][j+1] , dp[i][j] + b[i+1]);
			}
		}
	}
	printf("%d\n" , ans);
}
