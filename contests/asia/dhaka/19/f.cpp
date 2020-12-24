#include <bits/stdc++.h>

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

struct lazy_seg{
public:
	vector<pii>  st ;
	vector<int> lazy;
	lazy_seg(int n){
		st.resize(4*n + 1 , {0,0}) , lazy.resize(4*n + 1, 0);
	}
	lazy_seg() = default;
	void push(int l , int r , int curr){
		if(lazy[curr] != 0){
			st[curr].first += lazy[curr];
			if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
			lazy[curr] = 0 ;
		}
	}
	pii combine(pii a,  pii b){
		pii r;
		r.first = max(a.first, b.first);
		if(r.first == a.first) r.second += a.second;
		if(r.first == b.first) r.second += b.second;
		return r;
	}
	void pull(int l , int r , int curr){
		push(l,r,curr); int mid = l + (r-l)/2;
		if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
		st[curr] = combine(st[2*curr] , st[2*curr+1]);
	}
	void upd(int x , int y, int v,  int l, int r , int curr){
		int mid = (l+r)/ 2;  push(l,r,curr);
		if(l == x && r == y){
			lazy[curr] += v;
			push(l,r,curr);
			return ;
		}
		if(y <= mid) upd(x,y,v,l,mid,2*curr);
		else if(x > mid) upd(x,y,v,mid+1,r,2*curr+1);
		else upd(x,mid,v,l,mid,2*curr) , upd(mid+1,y,v,mid+1,r,2*curr+1);
		pull(l,r,curr);
	}
	pii qry(int x , int y , int l , int r , int curr){
		int mid = (l+r)/2; push(l,r,curr);
		if(l == x && r == y) return st[curr];
		if(y <= mid) return qry(x,y,l,mid,2*curr);
		else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
		return combine(qry(x,mid,l,mid,2*curr) , qry(mid+1,y,mid+1,r,2*curr+1));
	}
	void build(int l , int r,  int curr){
		int mid = (l+r)/2;
		if(l == r){
			st[curr] = {0,1}; 
			return ;
		}
		build(l,mid,2*curr);
		build(mid+1,r,2*curr+1);
		st[curr] = combine(st[2*curr]  , st[2*curr+1]);
	}
};

template<class T>
class HLD{
public:
	lazy_seg seg;
	HLD(int n): Sz(n+1) , Hd(n+1) , p(n+1, -1) , g(n+1) , out(n+1) , in(n+1) , n(n){
		seg = lazy_seg(n);
		seg.build(0 , n-1 , 1);
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
			seg.upd(in[Hd[y]] , in[y] ,v, 0 , n-1 , 1);
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) seg.upd(in[u] + 1 - (c? 1: 0) , in[y] , v, 0, n-1 , 1);
		return ;
	}
	pii combine(pii a,  pii b){
		pii r;
		r.first = max(a.first, b.first);
		if(r.first == a.first) r.second += a.second;
		if(r.first == b.first) r.second += b.second;
		return r;
	}
	pii query_path(int x , int y , bool c = 0){  
		int u = lca(x,y);
		pii ans = {0,0};
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			ans = combine(ans , seg.qry(in[Hd[y]] , in[y] , 0, n-1, 1));
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) ans = combine(ans ,seg.qry(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1)); 
		return ans;
	}
private:
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};


int32_t main(){
	int t;
	scanf("%d" , &t);
	int z = 0;
	while(t--){
		int n;
		scanf("%d" , &n);
		HLD<int> hld(n);
		rep(i,0,n-1){
			int x , y;
			scanf("%d%d" , &x , &y);
			hld.add_edge(x,y);
		}
		hld.decompose(1);
		int q;
		scanf("%d" , &q);
		printf("Case %d:\n" , ++z);
		while(q--){
			int k ;
			scanf("%d" ,&k);
			vpi tu(k);
			pii ans = {0,0};
			rep(j,0,k){
				scanf("%d%d" , &tu[j].first , &tu[j].second);
				hld.update_path(tu[j].first , tu[j].second,+1,1);
				ans = hld.query_path(tu[j].first,tu[j].second,1);
			}
			rep(j,0,k){
				hld.update_path(tu[j].first,tu[j].second,-1,1);
			}
			if(ans.first != k){
				ans.second = 0;
			}
			printf("%d\n" , ans.second);
		}
	}
}

