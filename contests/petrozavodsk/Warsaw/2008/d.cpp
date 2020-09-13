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
const int N = 200006;
int n , m , k , r;
vi g[N];

int bit[N];

void add(int x , int v){
	for(int i = x; i < N ; i += (i & -i))
		bit[i] = (bit[i] + v) % r;
}

int get(int x){
	int v = 0;
	for(int i = x ;i > 0 ; i -= (i & -i))
		v = (v + bit[i]) % r;
	return v;
}

void adiciona(int x , int v){
	add(x+1,v);
}

int busca(int x){
	return get(x+1);
}

int32_t main(){
	scanf("%d%d%d%d" , &n, &m, &k, &r);
	for(int i = 1 ; i <= k ; i ++){
		int h , w;
		scanf("%d%d" , &h, &w);
		g[h].push_back(w);
	}
	for(int i = 1 ;i <= n; i ++)
		sort(g[i].rbegin() , g[i].rend());
	adiciona(0,1);
	for(int i = 1; i <= n; i ++){
		for(auto w : g[i])
			adiciona(w , busca(w-1));
	}
	printf("%d\n" , busca(m));
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
