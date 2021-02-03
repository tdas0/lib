#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 100005;
int n; int S;
array<int,2> v[N];
int dp[2][2230];

int32_t main(){
	scanf("%d%d" , &n, &S);
	for(int i = 1 ; i <= n; i ++)
		scanf("%d" , & v[i][0]);
	for(int i = 1 ; i <= n; i ++){
		scanf("%d" , & v[i][1]);
	}
	for(int j = 0 ; j < 2230 ; j ++){
		if(j)
			dp[0][j] = dp[1][j] = S + 100;
	}
	sort(v+1 , v+n+1 , [&](array<int,2> a , array<int,2> b){
		return a[1] > b[1];
	});
	int ans = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= min(i , 2229) ; j ++){
			ll hu = min({(ll)dp[(i&1)^1][j] , (1ll*dp[(i&1)^1][j-1]) + (1ll*(j-1)) * (1ll*v[i][1]) + (1ll*v[i][0]), (ll)S+50});
			dp[i&1][j] = (int) hu;
			if(dp[i&1][j] <= S){
				ans = max(ans , j);
			}
		}
	}
	printf("%d\n" , ans);
}
