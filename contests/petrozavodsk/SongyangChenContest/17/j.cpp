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
const int N = 60005;
const int MAGIC = 200;
int dp[N][2 * MAGIC + 2] , A[N] , B[N] , n , k;
bool vis[N][2*MAGIC + 2];

int solve(int x , int d){
	if(d < -MAGIC)
		return 1000000;
	if(d > MAGIC)
		return 1000000;
	if(x == n + 1){
		return abs(d);
	}
	if(vis[x][d + MAGIC]){
		return dp[x][d+MAGIC];
	}
	vis[x][d + MAGIC] = 1;
	int a = solve(x +1 , d - 1) + 1; 
	if((x + d) <= N){
		a = min(a , solve(x ,d + 1) + 1);
		if(abs(A[x] - B[x + d]) > k)
			a = min(a , solve(x+1,d) + 1);
	}
	return dp[x][d+MAGIC] = a;
}

int32_t main(){
	scanf("%d%d" , &n , &k);
	for(int i = 1; i <= n ; i ++)
		scanf("%d" , &A[i]);
	for(int i = 1; i <= n ; i ++)
		scanf("%d" , &B[i]);
	printf("%d\n" , solve(1,0));
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
