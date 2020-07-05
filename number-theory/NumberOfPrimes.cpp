// pi(N) = number of primes not greater than N
// O(N^(2/3))
// Source: https://en.wikipedia.org/wiki/Meissel%E2%80%93Lehmer_algorithm
// Tested on: https://codeforces.com/contest/665/problem/F
// and on https://codeforces.com/gym/102576/problem/A
// Modified code from Emiso

const int N = 2e6 + 100; // > cbqrt(MAXN)

ll pref_pi[N];

const int NN = 2e5 + 100;
const int NP = 100;
ll dp[NN][NP];
vector<ll> primes;
// dp[i][j] -> number of K<=i such that its prime divisors are >= p[j]
bool isp[N];
void crivo(){
  for(int i=2;i<N;i++)isp[i] = 1;
  for(int i=1;i<N;i++){
    if(isp[i]){
      primes.pb(i);
      for(int j=2*i;j<N;j+=i)isp[j]=0;
    }
    pref_pi[i] = pref_pi[i-1] + isp[i];
  }

  // precalc the dp
  for(int i=1;i<NN;i++){
    dp[i][0] = i;
    for(int j=1;j<NP;j++){
      dp[i][j] = dp[i][j-1] - dp[i/primes[j-1]][j-1];
    }
  }
}

ll icbrt(ll x){
  int l = 1,r = 1e4;
  ll ans=1;
  while(l<=r){
    ll mid = (l+r)/2;
    if(mid * mid * mid <= x)ans = mid,l=mid+1;
    else r = mid-1;
  }
  if(ans * ans * ans < x)ans++;
  return ans;
}

ll solve(ll x,int k){
  if(x < NN and k<NP)return dp[x][k];
  if(k==0)return x;
  if(x < primes[k-1] * primes[k-1])return pref_pi[x] - (k-1);
  return solve(x,k-1) - solve(x/primes[k-1],k-1);
}

ll pi(ll x){
  if(x < N)return pref_pi[x];
  int k = pref_pi[icbrt(x)];
  ll res = solve(x,k) + (k-1);
  while(primes[k] * primes[k] <= x){
    res-=(pi(x/primes[k]) - k);
    k++;
  }
  return res;
}
