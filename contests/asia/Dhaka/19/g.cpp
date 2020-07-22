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
#include <limits>
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
template< class T = pii> 
struct ST{
	vector<T> st; int n; 
	T ini; 
	ST() = default;
	ST(int n , T ini = {INT_MAX, -1}) : st(2*n , ini) , n(n) , ini(ini) {}
	void upd(int pos, T val){ // pos 0index
		for(st[pos += n] = val ; pos /= 2;)
			st[pos] = min(st[2*pos] , st[2*pos + 1]);
	}
	T query(int x , int y){ // [x,y] , x, y -0index
		T ra = ini , rb = ini;
		for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
			if(x&1) ra = min(ra , st[x]) , x++;
			if(y&1) --y , rb = min(st[y] , rb);
		}
		return min(ra , rb);
	}
};

template <class T>
class Centroid{
public:
	vector<vector<T> > dist;
	vector<vi> tree;
	vi pai;
	vi level;
	vector<vi> in; // problem G Dhaka
	vector< ST<pii> > op;
	int n;
	Centroid(int n , int LGMAX = 20){
		this->n = n;
		g = vector< vector<pair< int, T> > >(n+1, vector<pair<int, T>>());
		dist = vector< vector<T> > (n+1 , vector<T>(LGMAX , numeric_limits<T>::max()));
		tree = vector<vi> (n+1 , vi());
		level = del = sz = pai = vi(n+1);
		in = vector<vi>(n+1, vi());
		op = vector< ST<pii> >(n+1 , ST<pii>());
	}
	void initq(){
		for(int i = 1; i <= n; i ++){
			sort(all(in[i]));
			op[i] = ST<pii>(sz(in[i]));
			for(int j = 0 ; j < sz(in[i]) ; j ++){
				op[i].upd(j,{dist[in[i][j]][level[i]] , in[i][j]});
			}
		}
	}
	pii query(int c , pii range){
		pii cur = pii(INT_MAX, - 1);
		int u = c;
		while(u != -1){
			int a = dist[c][level[u]];
			int L = lower_bound(all(in[u]) , range.first)  - begin(in[u]), R = upper_bound(all(in[u]) , range.second) - begin(in[u]) - 1;
			if(L <= R){
				pii b = op[u].query(L,R);
				cur = min(cur , {b.first + a, b.second}) ; 
			}
			u = pai[u];
		}
		return cur;
	}
	int calc_sz(int v,int p=-1){
	  sz[v] = 1;
	  for(auto to : g[v])if(to.F!=p and !del[to.F]){
	    sz[v]+=calc_sz(to.F,v);
	  }
	  return sz[v];
	}
	int find_centroid(int v,int p,int tam){
	  for(auto to : g[v])if(to.F!=p and !del[to.F]){
	    if(sz[to.F]*2>tam)return find_centroid(to.F,v,tam);
	  }
	  return v;
	}
	void dfs(int v,int root,int lv = 0, int p=-1,T d = 0){
		dist[v][lv] = d;
		in[root].push_back(v);
		for(auto w : g[v]) if(w.first != p && !del[w.first]){
			dfs(w.first,root,lv,v,d+w.second);
		}
	}
	void decompose(int v , int p = -1 , int lv = 0){
	  int tam = calc_sz(v);
	  int cent = find_centroid(v,-1,tam); 
	  dfs(cent, cent, lv); // answer querys if needed
	  del[cent] = 1;
	  if(p != -1){
	  	tree[cent].push_back(p);
	  	tree[p].push_back(cent);
	  }
	  pai[cent] = p;
	  level[cent] = lv;
	  for(auto to : g[cent]){
	    if(del[to.F])continue;
	    decompose(to.F,cent,lv+1);
	  }
	}	
	void add_edge(int x , int y , T z){
		g[x].push_back({y,z});
		g[y].push_back({x,z});
	}

	void build(){
		decompose(1);
	}
private:
	vector<vector<pair<int, T>> > g;
	vi del, sz;
};

int t , n , q;
map<int, pii> shop;

int32_t main(){
	scanf("%d" , &t);
	int zz = 0;
	while(t--){
		shop.clear();
		scanf("%d" , &n);
		Centroid<int> C(n);
		for(int i = 0 ; i< n -1 ; i++){
			int x , y ;
			scanf("%d%d" , &x , &y);
			C.add_edge(x,y,1);
		}
		C.build();
		C.initq();
		int q;
		printf("Case %d:\n", ++zz);
		scanf("%d" , &q);
		while(q--){
			int t;
			scanf("%d" , &t);
			if(t == 1){
				int x , l, r;
				scanf("%d%d%d" , &x , &l , &r);
				shop[x] = {l,r};
			}
			else if(t == 2){
				int x;
				scanf("%d" , &x);
				shop.erase(x);
			}
			else{
				int c , m;
				scanf("%d%d" , &c , &m);
				pii ans = {INT_MAX, -1};
				for(int j = 0 ; j < m ; j ++){
					int x;
					scanf("%d" , &x);
					if(shop.count(x)){
						if(shop[x].first <= c && c <= shop[x].second){
							ans = {0 , c};
						}
						ans = min(ans , C.query(c, shop[x]));
					}
				}
				if(ans.first == INT_MAX) printf("-1\n");
				else printf("%d\n" , ans.first);
			}
		}
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