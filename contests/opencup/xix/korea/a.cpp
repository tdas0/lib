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


struct Range{
	Range(int l = -1) : l(l){}
	Range(int l, int r, int v) : l(l) , r(r) , v(v) {}
	int l , r;
	int v;
	bool operator<(const Range &rhs) const { return l < rhs.l; }
};

template <class T = int>
class ColorUpdate{
public:
	vector<Range> upd(int l , int r , T v){
		vector<Range> ans; 
		if(l > r) return ans;
		auto it = ranges.lower_bound(l);
		if(it != ranges.begin()){
			it--;
			if(it->r > l){
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.l, l, cur.v));
				ranges.insert(Range(l, cur.r, cur.v));
			}
		}
		it = ranges.lower_bound(r);
		if(it != ranges.begin()){
			it--;
			if(it->r > r){
				auto cur = *it;
				ranges.erase(it);
				ranges.insert(Range(cur.l, r, cur.v));
				ranges.insert(Range(r, cur.r, cur.v));
			}
		}
		for(it = ranges.lower_bound(l) ; it != ranges.end() && it->l < r ; it++){
			ans.push_back(*it);
		}
		ranges.erase(ranges.lower_bound(l) , ranges.lower_bound(r));
		ranges.insert(Range(l,r,v));
		return ans;
	}
	Range rangeof(int l){
		auto u = ranges.lower_bound(l+1);
		if(u == ranges.begin()){
			return Range();
		}
		return *prev(u);
	}
private:
	set<Range> ranges;  
};

const int N = 200005;
int qnt[N] , n , C, q , rf[N];
template<class T>
class HLD{
public:
	ColorUpdate<int> cor;
	HLD(int n): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
		cor.upd(0 , n , 0);
	}
	void add_edge(int x , int y){
		g[x].push_back(y);
		g[y].push_back(x);
		edges ++ ;
		assert(edges < n);
	}
	void dfs_sz(int x , int par = -1){
		Sz[x] = 1;
		trav(w, g[x]){
			if(w == par) continue;
			dfs_sz(w,x);
			Sz[x] += Sz[w];
			if(Sz[w] > Sz[g[x][0]] || g[x][0] == par) swap(w, g[x][0]);
		}
	}
	void dfs_dec(int x , int par = -1){ 
		in[x] = tin++;
		allin(w, g[x]){
			if(w == par) continue;
			p[w] = x;
			Hd[w] = ((w == g[x][0]) ? Hd[x] : w);
			dfs_dec(w,x); 
		}
		out[x] = tin;
	}
	void decompose(int root){
		Hd[root] = root;
		dfs_sz(root);
		dfs_dec(root);
	}
	int lca(int x , int y){
		while(Hd[x] != Hd[y]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			y = p[Hd[y]];
		}
		return in[x] < in[y] ? x : y ;
	}
	void update_path(int x , int y , T v , bool c = 0){
		int u = lca(x,y);
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			vector<Range> zu = cor.upd(in[Hd[y]] , in[y]+1 , v);
			for(auto w : zu){
				rf[qnt[w.v]] -- ;
				qnt[w.v] -= w.r - w.l;
				rf[qnt[w.v]] ++ ;
				rf[qnt[v]] --;
				qnt[v] += w.r - w.l;
				rf[qnt[v]] ++ ;
			}

		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]){ 
			vector<Range> zu = cor.upd(in[u] + 1 - (c? 1: 0) , in[y]+1 , v);
			for(auto w : zu){
				rf[qnt[w.v]] -- ;
				qnt[w.v] -= w.r - w.l;
				rf[qnt[w.v]] ++ ;
				rf[qnt[v]] --;
				qnt[v] += w.r - w.l;
				rf[qnt[v]] ++ ;
			}
		}
		return ;
	}

private:
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};

int32_t main(){
	scanf("%d%d%d" , &n , &C , &q);
	HLD<int> hld(n);
	qnt[0] = n -1;
	rf[qnt[0]] += 1;
	rf[0] += C ;
	for(int i = 0 ; i < n - 1; i ++){
		int a , b;
		scanf("%d%d" , &a , &b);
		hld.add_edge(a,b);
	}
	hld.decompose(1);
	while(q--){
		int u , c, m;
		scanf("%d%d%d" , &u , &c , &m);
		hld.update_path(1,u,c);
		printf("%d\n" , rf[m] - (qnt[0] == m ? 1 : 0));
	}
}
