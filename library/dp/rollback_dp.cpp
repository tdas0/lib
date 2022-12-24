// finds the values that can be made with active elements
// https://codeforces.com/contest/981/problem/E
// sometimes is better to use d&c instead: https://codeforces.com/contest/303/submission/186565932

int dp[N];
int n;
const int M = 998244353;
const int M2 = 1e9+7;
int dp2[N];
void add(int x){
  for(int i=n;i>=x;i--){
    dp[i]+=dp[i-x];
    dp2[i]+=dp2[i-x];
    if(dp[i]>=M)dp[i]-=M;
    if(dp2[i]>=M2)dp2[i]-=M2;
  }
  for(int i=1;i<=n;i++)if(dp[i]|dp2[i])ok[i]=1;
}
void rem(int x){

  for(int i=x;i<=n;i++){
    dp[i]-=dp[i-x];
    dp2[i]-=dp2[i-x];
    if(dp[i]<0)dp[i]+=M;
    if(dp2[i]<0)dp2[i]+=M2;
  }
  for(int i=1;i<=n;i++)if(dp[i]|dp2[i])ok[i]=1;
}

// Roll back to number of subsequences of string w == s:
void add(char x){
  for(int jump = m-1;jump>=0;jump--){
    for(int i=0;i + jump < m;i++){
      int j = i + jump;
      if(s[j] == x){
        // jump from i->j using j-1 as a pivo
        mat[i][j] = (mat[i][j] + (i == j ? 1 : mat[i][j-1]))%M;
      }
    }
  }
}
void rem(char x){
  for(int jump=0;jump<m;jump++){
    for(int i=0; i + jump < m;i++){
      int j = i + jump;
      if(s[i] == x){
        // erase the path i -> j using i+1 as a pivo
        mat[i][j] = (mat[i][j] + M - (i == j ? 1 : mat[i+1][j]))%M;
      }
    }
  }
}
