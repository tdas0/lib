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

const int N = 303;
const int M = 100005;
int n;
bitset<N> f[M];
bitset<N> g[M];
int phage[N][N] , sz[N];

int32_t main(){
	scanf("%d" , &n);
	for(int i = 1 ; i <= n; i ++){
		scanf("%d" , &sz[i]);
		for(int j = 1 ; j <= sz[i] ; j ++)
			scanf("%d" , &phage[i][j]) ,f[phage[i][j]][i] = 1;
	}	
	for(int i = 1 ; i <= n; i ++){
		int soma = 0;
		for(int j = 1 ; j <= sz[i] ; j ++){
			for(int k = j + 1; k <= sz[i] ; k ++){
				soma += ((f[phage[i][j]]) & (~ f[phage[i][k]])).count()  * ((~f[phage[i][j]]) & (f[phage[i][k]])).count()  ;
			}
		}
		printf("%d\n" , soma);
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
