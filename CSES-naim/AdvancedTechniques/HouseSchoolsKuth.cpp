/*
 Construir K escolas de modo que toda crianca paga |a-b| para ir para a escola mais perto
 Tem ci criancas na casa i
 Achar menor custo total
*/

const int N = 6161;
ll B,C;
 
ll H[N];
const ll inf = 1e18;
ll cost[N][N];
 
 
pll dp[N][N];
bool vis[N][N];
pll solve(int i,int j){
	if(vis[i][j])return dp[i][j];
	vis[i][j] = 1;
	if(i == 1)return dp[i][j] = pll(cost[1][j],1);
	if(i >= j)return dp[i][j] = pll(B*i,j);
	int optr = solve(i+1,j).ss,optl = solve(i,j-1).ss;
	dp[i][j] = pll(inf,inf);
	for(int k = max(1,optl);k<=min(optr,j);k++){
		ll custo = solve(i-1,k-1).ff + cost[k][j];
		int cur = k;
		dp[i][j] = min(dp[i][j],pll(custo,cur));
	}
	return dp[i][j];
}
 
int32_t main(){
  fastio;
  int n;
  int k;
  cin >> n >> k; //>> B >> C;
  B=0,C=1;
  rep(i,1,n+1)cin >> H[i] , H[i] = 1ll * H[i] * C;
 
  for(int l = 1;l<=n;l++){
    cost[l][l] = B;
    int ptr=l;
    ll L=H[l],R=0;
    ll custo=B;
    for(int r = l +1;r<=n;r++){
      
      custo+=(r - ptr) * H[r];
      if(r!=ptr)R+=H[r];
      else L+=H[r];
  
      /*
      while(ptr > l and (R+H[ptr]) - (L - H[ptr]) < 0){
        custo+=(R + H[ptr]) - (L - H[ptr]);
        R+=H[ptr];
        L-=H[ptr];
        ptr--;
      }
      */
      
      while(ptr<r and L - R < 0){
        custo+=L-R;
        R-=H[ptr+1];
        L+=H[ptr+1];
        ptr++;
      }
      cost[l][r] = custo;
    }
  }
  cout << solve(k,n).ff << endl;
}
