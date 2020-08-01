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
const int N = 250005;

int n, k , to[N];
ll dp[N][2]; // 0 = não posso pegar o vértice, 1 = posso pegar o vértice
vpi g[N];
ll ans = - (ll) 1e18;
vi cost;
void dfs(int x , ll cnstr, int p = -1){
	ll best = 0 , optbest = -1;
	for(auto w: g[x]){
		if(w.first == p) continue;
		dfs(w.first,cnstr,x);
		dp[x][0] += dp[w.first][1];
		dp[x][1] += dp[w.first][1];
		if((dp[w.first][0] - dp[w.first][1] + w.second + cnstr) > best){
			best = dp[w.first][0] - dp[w.first][1] + w.second + cnstr;
			optbest = w.first;
		}
	}		
	to[x] = optbest;
	dp[x][1] += best;
}

void recover(int x , int y , ll cnstr , int p = -1){
	for(auto w : g[x]){
		if(w.first == p) continue;
		if(y == 0){
			recover(w.first, 1, cnstr, x);
		}
		else{
			if(to[x] == -1){
				recover(w.first, 1, cnstr , x);
			}
			else{
				if(w.first == to[x]){
					cost.push_back(w.second);
					recover(w.first, 0 , cnstr , x);
				}
				else{
					recover(w.first,1,cnstr,x);
				}
			}
		}
	}
}

void solve(ll cnstr , ll &l , ll &r){
	for(int i = 1; i <= n; i ++){
		for(int j = 0 ; j < 2; j ++)
			dp[i][j] = 0 ;
		to[i] = 0;
	}
	cost.clear();
	dfs(1,cnstr);
	recover(1,1,cnstr);
	if(sz(cost) >= k){
		r = cnstr - 1;
		sort(all(cost));
		reverse(all(cost));
		ll z = 0;
		for(int j = 0 ; j < k ; j ++){
			z += cost[j];
		}
		ans = z;
	}
	else{
		l = cnstr + 1;
	}
}





int32_t main(){
	scanf("%d%d" , &n , &k);
	for(int i = 1; i < n; i ++){
		int a , b, c;
		scanf("%d%d%d" , &a , &b,  &c);
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	ll l = - (ll) 1e12L , r = (ll) 1e12L;
	while(l <= r){
		solve(l + (r-l)/2ll , l , r);
	}
	if(ans == -(ll) 1e18)
		printf("Impossible\n");
	else{
		printf("%lld\n" , ans);
	}
}