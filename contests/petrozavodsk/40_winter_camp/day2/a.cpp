#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1005;

const ll mod = (int) 1e9 + 7;

ll dp[N][N][2];
bool vis[N][N][2];


ll solve(int n, int k , int w){
	if(k < 0)
		return 0;
	if(k >= n)
		return 0;
	if(n == 1){
		return (!k && !w);
	}
	if(vis[n][k][w])
		return dp[n][k][w];
	vis[n][k][w] = true;
	dp[n][k][w] = 0;
	if(w)
		dp[n][k][w] = (dp[n][k][w] + solve(n-1,k-1,0)*2ll + solve(n-1,k-1,1) + solve(n-1,k,1))%mod; // ok
	else{
		dp[n][k][w] = (dp[n][k][w] + solve(n-1,k+1,0)*((ll)k + 1)  + solve(n-1,k+1,1)*((ll)k)) % mod; 
		dp[n][k][w] = (dp[n][k][w] + solve(n-1,k,0)*((ll)n - k -2) + solve(n-1,k,1)*((ll) n - k - 1))%mod;
	}
	return dp[n][k][w];
}



int32_t main(){
	int t;
	scanf("%d" , &t);
	while(t--){
		int n, k;
		scanf("%d%d" , &n, &k);
		printf("%lld\n" , (solve(n,k,1) + solve(n,k,0))%mod);
	}
}
