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
const int base = 3;
int dp[1594323] , pw[14], a[1594323];
string s;
int get_mask(int mask, int i){
	return (mask/pw[i]) % base;
}

int32_t main(){
	pw[0] = 1;
	for(int j = 1; j < 14 ; j++)
		pw[j] = pw[j-1] * 3;
	int t;
	cin >> t;
	while(t--){
		int n , k;
		cin >> n >> k;
		rep(i,0,pw[k])
			a[i] = 0 , dp[i] = 0;
 		for(int i = 0 ; i < n; i ++){
			cin >> s;
			int p = 0;
			for(int j = 0 ; j < k ; j++){
				p = 3*p + (s[j] == '1');
			}
			a[p] ++; 
		}
		for(int i = 1 ; i < pw[k] ; i ++){
			for(int j = 0 ; j < k ; j ++){
				if(get_mask(i,j) == 2){
					int u = i - pw[j]*2 , v = u + pw[j];
					a[i] += a[u] + a[v];
					break ; 
				}
			}
		}
		for(int i = 1 ; i < pw[k] ; i ++){
			int cur = k ;
			for(int j = 0 ; j < k ; j ++){
				if(get_mask(i,j) == 2){
					int u = i - pw[j]*2 , v = u + pw[j];
					cur = min(cur , max(dp[u] , dp[v]) + 1);
				}
			}
			dp[i] = cur * (a[i] > 1);
		}
		cout << dp[pw[k] - 1] << endl;
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
