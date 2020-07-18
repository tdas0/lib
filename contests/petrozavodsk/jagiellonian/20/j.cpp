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

struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		rep(i,0,n+1) p[i] = i;
	}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};	

const int N = 1000005;

int t , n , x[N] , y[N] , z[N] , q;
int32_t main(){
	scanf("%d" , &t);
	while(t--){
		scanf("%d" , &n);
		dsu T(n + 3);
		map<array<int,3> , int > go; 
		map<int, vi> pai[3][3];
		for(int i = 1; i <= n; i++){
			scanf("%d%d%d" , &x[i] , &y[i] , &z[i]);
			int xi = x[i] , yi = y[i] , zi = z[i];
			for(x[i] = xi - 1 ; x[i] <= xi + 1 ; x[i] ++){
			for(y[i] = yi - 1 ; y[i] <= yi + 1 ; y[i] ++){
			for(z[i] = zi -1 ; z[i] <= zi + 1 ; z[i] ++){
			if(xi == -1 && x[i] != xi) continue;
			if(yi == -1 && y[i] != yi) continue;
			if(zi == -1 && z[i] != zi) continue;
			int cost = abs(x[i] - xi) + abs(y[i] - yi) + abs(z[i] - zi);
			if(cost > 1) continue;
			if(go.count({x[i],y[i],z[i]})) T.join(i , go[{x[i] , y[i] , z[i]}]);
			if(x[i] == -1){ // (z-1, y,  z);
				if(pai[1][2].count(z[i])){ 
					for(auto w : pai[1][2][z[i]])
						T.join(i, w); // (x, -1 , z) 
					pai[1][2][z[i]].clear();
					pai[1][2][z[i]].push_back(i);
				}
				if(pai[2][1].count(y[i])){
					for(auto w : pai[2][1][y[i]])
						T.join(i, w);  // (x,  y, -1)
					pai[2][1][y[i]].clear();
					pai[2][1][y[i]].push_back(i);
				} 
				if(x[i] == xi && yi == y[i] && zi == z[i]){
					pai[0][1][y[i]].push_back(i);
					pai[0][2][z[i]].push_back(i);
				}
			}
			else if(y[i] == -1){	
				if(pai[0][2].count(z[i])){ 
					for(auto w : pai[0][2][z[i]])
						T.join(i,w);
					pai[0][2][z[i]].clear();
					pai[0][2][z[i]].push_back(i);
				}
				if(pai[2][0].count(x[i])) {
					for(auto w : pai[2][0][x[i]])
						T.join(i,w);
					pai[2][0][x[i]].clear();
					pai[2][0][x[i]].push_back(i);
				}
				if(x[i] == xi && y[i] == yi && z[i] == zi){
					pai[1][0][x[i]].push_back(i);
					pai[1][2][z[i]].push_back(i);
				}
			}
			else if(z[i] == -1){
				if(pai[0][1].count(y[i])){
					for(auto w : pai[0][1][y[i]])
					 	T.join(i,w);
					pai[0][1][y[i]].clear();
					pai[0][1][y[i]].push_back(i);
				}
				if(pai[1][0].count(x[i])) {
					for(auto w : pai[1][0][x[i]])
						T.join(i, w);
					pai[1][0][x[i]].clear();
					pai[1][0][x[i]].push_back(i);
				}
				if(x[i] == xi && y[i] == yi && z[i] == zi){
					pai[2][0][x[i]].push_back(i);
					pai[2][1][y[i]].push_back(i);
				}
			}}}}
			go[{xi,yi,zi}] = i;
		}
		scanf("%d" , &q);
		while(q--){
			int x1 , y1 , z1 , x2 , y2 , z2;
			scanf("%d%d%d%d%d%d" , &x1 , &y1 , &z1 , &x2 , &y2 , &z2);
			set<int> comps;
			if(go.count({x1,y1,-1})) comps.insert(T.find(go[{x1,y1,-1}]));
			if(go.count({x1,-1,z1})) comps.insert(T.find(go[{x1,-1,z1}]));
			if(go.count({-1,y1,z1})) comps.insert(T.find(go[{-1,y1,z1}]));
			bool ok = false;
			swap(x1,x2) , swap(y1, y2) , swap(z1, z2);
			if(go.count({x1,y1,-1})){
				ok |= (comps.count(T.find(go[{x1,y1,-1}])));
			}
			if(go.count({x1,-1,z1})){
				ok |= (comps.count(T.find(go[{x1,-1,z1}])));
			}		
			if(go.count({-1,y1,z1})){
				ok |= comps.count(T.find(go[{-1,y1,z1}]));
			}
			printf(ok ? "YES\n" :"NO\n");
		}
	}
}

