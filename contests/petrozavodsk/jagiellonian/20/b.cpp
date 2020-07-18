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
const int N = 1000005;

ll dp[N] ;
int a[N] ;
int t, n;

int32_t main(){
	scanf("%d" , &t);
	while(t--){
		scanf("%d" , &n);
		ll mx = 0;
		for(int i = 1; i <= n; i ++){
			scanf("%d" ,&a[i]) , dp[a[i]] ++ ;
			mx = max((ll)a[i] , mx);
		}
		for(int j = 0 ; j < 21 ; j ++){
			for(int i = 0 ; i <= mx ; i ++){
				if((1<<j) & i)
					dp[i] += dp[i ^ (1<<j)];
			}
		}
		ll ans = 0;
		for(int i = 1 ;i <= n; i++){
			ans += dp[a[i]];
		}
		printf("%lld\n" , ans);
		for(int i = 0 ; i <= mx ; i ++) dp[i] = 0;
	}
}

