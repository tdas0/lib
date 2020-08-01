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
const int N = 300005;
vi g[N] , rg[N];
int l[N] , r[N] , n , m , dg[N] , rdg[N];
bool vis[N]; 
int pos[N] , rpos[N];
vi beg[N];
multiset<pii> opt;
int32_t main(){
	scanf("%d%d" , &n ,&m);
	for(int i = 1; i <= n; i++){
		scanf("%d%d" , &l[i] , &r[i]);
	}
	for(int i = 0 ; i < m ; i ++){
		int x , y;
		scanf("%d%d" , &x , &y);
		g[y].push_back(x);
		rg[x].push_back(y);
		dg[x] ++ , rdg[y] ++ ;
	}
	queue<int> q;
	for(int i = 1; i <= n; i++){
		if(dg[i] == 0){
			q.push(i);
		}
	}	
	while(sz(q)){
		int u = q.front();
		q.pop();
		vis[u] = true;
		for(auto w : g[u]){
			r[w] = min(r[w] , r[u] - 1);
			dg[w] -- ;
			if(dg[w] == 0) q.push(w);
		}
	}
	for(int i = 1; i <= n; i ++){
		if(rdg[i] == 0) q.push(i);
	}
	while(sz(q)){
		int u = q.front();
		q.pop();
		for(auto w : rg[u]){
			l[w] = max(l[w] , l[u] + 1);
			rdg[w] -- ;
			if(rdg[w] == 0) q.push(w);
		}
	}
	bool ok = 1;
	for(int i = 1; i <= n; i ++){
		ok &= vis[i];
		if(l[i] > r[i]) ok = false;
		l[i] = max(l[i] , 1);
		r[i] = min(r[i] , n);
		if(l[i] > r[i]) ok = false;
		beg[l[i]].push_back(i);
	}
	for(int i = 1; i <= n; i ++){
		for(auto w : beg[i]){
			opt.insert({r[w] , w});
		}
		while(sz(opt) && !pos[i]){
			auto u = *begin(opt);
			opt.erase(begin(opt));
			if(u.first >= i){
				pos[i] = u.second;
				rpos[u.second] = i;
			}
		}
	}
	// line sweep
	set<int> rx;
	for(int i = 1; i <= n; i ++){
		if(!pos[i]){
			ok = false;
		}
		rx.insert(pos[i]);
		if(!(l[i] <= rpos[i] && rpos[i] <= r[i])){
			ok = false;
		}
	}
	if(sz(rx) != n) ok = false;
	if(ok){
		for(int i = 1; i <=n ; i ++){
			printf("%d\n" , pos[i]);
		}
	}
	else printf("-1\n");
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/