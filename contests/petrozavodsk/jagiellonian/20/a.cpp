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

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
const int N = 200005;
const int MAGIC = 4160000;
const int CSQ = 225;

bool isp[MAGIC];
vi primes;
ll n;
int sj[MAGIC] , dp[N][CSQ];

ll icbrt(ll x){
	ll u = cbrt(x);
	if(u*u*u < x) return u + 1;
	return u;
}

ll solve(ll i ,int j){
	if(j == 0) return i;
	if(i < (primes[j] * 1ll) * (primes[j]*1ll) && i < MAGIC){
		return max(1 ,sj[i] - (j-1));
	}
	if(i < N && j < CSQ) return dp[i][j];
	return solve(i,j-1) - solve(i/primes[j-1],j-1);
}


ll pi(ll x){
	if(x < MAGIC) return sj[x];
	ll opt = icbrt(x);
	ll ans = solve(x,opt) + (opt - 1);
	while((1ll*primes[opt])*(1ll*primes[opt]) <= x){
		ans -= pi(x/primes[opt]) - (opt);
		opt ++;
	}	
	return ans;
}

int32_t main(){
	rep(i,2,MAGIC){
		if(!isp[i]){
			sj[i] ++ ;
			primes.push_back(i);
			for(int j = 2*i ; j < MAGIC ; j += i) isp[j] = 1;	
		}
		sj[i] += sj[i-1];
	}
	rep(i,1,N){
		dp[i][0] = i;
		rep(j,1,CSQ){
			dp[i][j] = dp[i][j-1] - dp[i/primes[j-1]][j-1];
		}
	}
	int t;
	scanf("%d" , &t);
	while(t--){
		ll n;
		scanf("%lld" , &n);
		ll less = pi(n) - pi(n/2);
		printf("%lld\n" , n - ((n - less-1) / 2));
	}
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/