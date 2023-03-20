// contar numero de formas de colocar K bispos que nao se ataquem
// tab NxN. n<=500, k<=n^2
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
using namespace std;
 
int squares(int i){
  if(i&1)return i/4*2 + 1;
  return (i-1)/4*2 + 2;
}
const int N = 500 * 2 + 2;
long long dp[N][N];
 const int M = 1e9 + 7;
int32_t main(){
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  for(int i=0;i<N;i++)dp[i][0] = 1;
  dp[1][1] = 1;
  int n,k;
  cin >> n >> k;
  if(k > 2*n - 1)return cout << 0 << "\n",0;
  rep(i,2,2*n){
    for(int j=1,sq = squares(i);j<=sq;j++){
      dp[i][j] = dp[i-2][j] + dp[i-2][j-1]*(sq - j + 1);
      dp[i][j]%=M;
    }
  }
 
  long long res=0;
  for(int i=0;i<=k;i++){
    res = (res + 1ll*dp[2*n-1][i]*dp[2*n-2][k-i])%M;
  }
  cout << res << "\n";
 
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}