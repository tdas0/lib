#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

const int N = 505;

typedef long long ll;

int x[N] , t[N] , y[N] , r[N], n , s1 , s2;
ll dp[2][N][N];
array<int,4> gg[N];

int32_t main(){
	scanf("%d%d%d" , &n , &s1 ,&s2);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d%d%d" , &x[i] , &t[i] , &y[i] , &r[i]);
		gg[i] = {x[i] , t[i] , y[i] , r[i]};
	}
	sort(gg+1,gg+1+n);
	for(int i = 1; i <= n; i ++){
		x[i] = gg[i][0] , t[i] = gg[i][1] , y[i] = gg[i][2] , r[i] = gg[i][3];
	}
	for(int i = 0 ; i <= s1 ;i ++)
		for(int j = 0 ;j <= s2; j ++)
			dp[0][i][j] = dp[1][i][j] = (ll) 1e18;
	dp[1][0][0] = 0;
	for(int i = 1; i <= n; i ++){
		int cur = i&1 , nx = cur ^ 1;
		for(int j = 0 ; j <= s1; j ++){
			for(int k = 0 ; k <= s2; k ++){
				// pegar o item i como level 1
				int la , lb;
				if(j != s1){
					la = (j + x[i]) , lb = k;
					if(la > s1) lb += la - s1, la = min(la , s1);
					if(lb > s2) lb = min(lb, s2);
					dp[nx][la][lb] = min(dp[cur][j][k] + t[i], dp[nx][la][lb]);
				}
				// pegar o item i como level 2
				la = j , lb = min(k + y[i], s2);
				dp[nx][la][lb] = min(dp[cur][j][k] + r[i] , dp[nx][la][lb]);
				// não pegar nenhum item
				dp[nx][j][k] = min(dp[nx][j][k] , dp[cur][j][k]);
			}
		}
	}
	if(dp[(n+1)&1][s1][s2] >= (ll) 1e16)
		dp[(n+1)&1][s1][s2] = -1;
	printf("%lld\n" , dp[(n+1)&1][s1][s2]);
}
 
