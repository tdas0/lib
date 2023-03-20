/*
Given an array of n numbers, your task is to divide
it into nsubarrays, each of which has a single element.
On each move, you may choose any subarray and split it into two subarrays.
The cost of such a move
is the sum of values in the chosen subarray.
What is the minimum total cost if you act optimally?
*/
const int N = 5050;
int x[N];
ll dp[N][N];
int opt[N][N];
ll pre[N];
int32_t main(){
  fastio;
  int n;
  cin >> n;
  rep(i,1,n+1)cin >> x[i],pre[i]=pre[i-1]+x[i];
  rep(t,1,n+1){
    for(int l=1;l+t-1<=n;l++){
      if(t==1){
        dp[l][l] = 0;
        opt[l][l]=l;
        continue;
      }
      int r = l+t-1;
      dp[l][r] = 1e18;
      for(int k= opt[l][r-1];k<=opt[l+1][r];k++){
        ll cost = dp[l][k] + dp[k+1][r] + pre[r]-pre[l-1];
        if(dp[l][r]  > cost){
          dp[l][r]=cost;
          opt[l][r]=k;
        }
      }
    }
  }
  cout << dp[1][n] << endl;
}