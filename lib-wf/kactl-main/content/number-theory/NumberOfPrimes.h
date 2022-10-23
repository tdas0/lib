/**
 * Author: Emiso
 * Description: $pi(N) = #primes \leq N$
 * Size of array fixed for N=1e11. around MAXN^(2/3) 
 * Also, could use linear sieve
 * $dp[i][j] = $number of $K \leq i$ | its prime divisors are $\geq p[j]$
 * Time: O(N^(2/3))
 */

const int N = 2e6 + 100; 

ll prefPi[N];

const int NN = 2e5 + 100;
const int NP = 100;
ll dp[NN][NP];
vector<ll> primes;
bool isp[N];
void crivo(){
  for(int i=2;i<N;i++)isp[i] = 1;
  for(int i=1;i<N;i++){
    if(isp[i]){
      primes.pb(i);
      for(int j=2*i;j<N;j+=i)isp[j]=0;
    }
    prefPi[i] = prefPi[i-1] + isp[i];
  }
  for(int i=1;i<NN;i++){
    dp[i][0] = i;
    for(int j=1;j<NP;j++){
      dp[i][j] = dp[i][j-1] - dp[i / primes[j-1]][j-1];
    }
  }
}

ll icbrt(ll x){
  int l = 1,r = 1e4;
  ll ans=1;
  while(l<=r){
    ll mid = (l+r) / 2;
    if(mid * mid * mid <= x)ans = mid,l=mid+1;
    else r = mid-1;
  }
  if(ans * ans * ans < x)ans++;
  return ans;
}

ll solve(ll x,int k){
  if(x < NN and k<NP)return dp[x][k];
  if(k==0)return x;
  if(x < primes[k-1] * primes[k-1] && x < N)return max(1ll,prefPi[x] - (k-1));
  return solve(x,k-1) - solve(x / primes[k-1],k-1);
}

ll pi(ll x){
  if(x < N)return prefPi[x];
  int k = prefPi[icbrt(x)];
  ll res = solve(x,k) + (k-1);
  while(primes[k] * primes[k] <= x){
    res-=(pi(x / primes[k]) - k);
    k++;
  }
  return res;
}
