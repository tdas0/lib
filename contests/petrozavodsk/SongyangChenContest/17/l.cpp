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
const int N = 2020;
const int mod = 998244353;

int dp[N][N][2] , bit[N][N][2];
int n, m , a[N] , b[N];

void modsum(int &x , int y){
	x = (x + y);
	if(x > mod){
		x -= mod;
	}
	if(x < 0){
		x += mod;
	}
}

void add(int x , int y , int z , int v){
	for(int i = x; i < N ; i += (i&-i)){
		for(int j = y ; j < N ; j += (j&-j)){
			modsum(bit[i][j][z] , v);
		}
	}
}

int get(int x , int y , int z){
	if(x <= 0 || y <= 0) return 0;
	int s = 0;
	for(int i = x; i > 0 ; i -= (i&-i)){
		for(int j = y ; j > 0 ; j -= (j&-j)){
			modsum(s , bit[i][j][z]);
		}
	}	
	return s;
}

int query(int x1 , int y1 , int x2 , int y2 , int z){
	if(x1 < x2 || y1 < y2)
		return 0;
	int s = 0 ;
	modsum(s,get(x1,y1,z));
	modsum(s, - get(x1,y2-1,z));
	modsum(s , -get(x2-1,y1,z));
	modsum(s , get(x2-1,y2-1,z));
	return (s);
}


int32_t main(){
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n; i ++){
		scanf("%d" , &a[i]);
	}
	for(int i = 1 ; i <= m ; i ++){
		scanf("%d" , &b[i]);
	}	
	int ans = 0;
	for(int i = 1 ; i <= n; i ++){
		for(int j = 1 ; j <= m ; j ++){
			if(a[i] == b[j]){
				dp[i][j][0] = 1 , dp[i][j][1] = 0;
				modsum(dp[i][j][0] , query(N-1, j - 1, a[i] + 1, 1 , 1));
				modsum(dp[i][j][1] , query(a[i]-1, j-1, 1, 1, 0));
				modsum(ans, dp[i][j][0]);
				modsum(ans , dp[i][j][1]);
				add(a[i] , j , 0 , dp[i][j][0]);
				add(a[i] , j , 1 , dp[i][j][1]);
			}
		}
	}
	if(ans < 0)
		ans += mod;
	printf("%d\n" , ans);
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
