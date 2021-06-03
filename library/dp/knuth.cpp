const int N = 5005;
ll s[N] , dp[N][N][55];
int opt[N][N][55];
int n , k;
void solve(){
	scanf("%d%d" , &n , &k);
	for(int i = 1 ; i <= n; i ++){
		scanf("%lld" , &s[i]);
		dp[i][i] = 0 , opt[i][i] = i;
	}
	for(int h = 1 ; h <= k ; h ++){
		for(int len = 2; len <= n; len ++){
			for(int i = 1 , j = len ; j <= n; i ++ , j ++){
				dp[i][j] = s[j] - s[i-1] + dp[i][opt[i][j-1]] + dp[opt[i][j-1] + 1][j];
				opt[i][j] = opt[i][j-1];
				for(int k = opt[i][j-1]  ; k <= opt[i+1][j] ; k ++){
					if(dp[i][j] > (s[j] - s[i-1]) + dp[i][k] + dp[k+1][j]){
						opt[i][j] = k;
						dp[i][j] = s[j] - s[i-1] + dp[i][k] + dp[k+1][j];
					}
				}
			}
		}
	}
	printf("%lld\n" , dp[1][n]);
}


int32_t main(){
	solve();
}
