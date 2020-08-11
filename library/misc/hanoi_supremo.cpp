/* Resolve o Hanoi generalizado pra M pegs
 * O(M * qtd de movimentos)
 * Status: Tested on ASC2 - B
 */
int N,M;
const ll inf = 1e15;
ll dp[66][66];
int best[66][66];

vi peg[70];

void solve(int n,int m,int from,int to){
  // n disc, m pegs. Im at from and want to move it all to "to"
  if(n == 1){
   
    printf("move %d from %d to %d",peg[from].back(),from,to);
    if(sz(peg[to]))printf(" atop %d\n",peg[to].back());
    else printf("\n");

    peg[to].pb(peg[from].back());
    peg[from].pop_back();
    return;
  }
  int k = best[n][m];
  int vazio = M;
  for(int i = 1;i<=M;i++){
    if((sz(peg[i])==0 or peg[i].back() > peg[from][sz(peg[from])-k]) and i!=to){
      vazio = i;break;
    }
  }
  

  solve(n-k,m,from,vazio);
  solve(k,m-1,from,to);
  solve(n-k,m,vazio,to);
  return;
}

void prepare(){
   for(int i=1;i<=N;i++){
    for(int j=1;j<=M;j++){
        best[i][j] = 1;
      if(j == 1){
        dp[i][j] = inf;
      }else if(i == 1){
        dp[i][j] = 1;
      }else{
        dp[i][j] = inf;
        for(int k=1;k<i;k++){
          if(dp[i-k][j] * 2ll + dp[k][j-1] < dp[i][j]){
            dp[i][j] = dp[i-k][j] * 2ll + dp[k][j-1];
            best[i][j] = k;
          }
        }

      }
    }
  }
  for(int i=N;i>=1;i--)peg[1].pb(i);
}
