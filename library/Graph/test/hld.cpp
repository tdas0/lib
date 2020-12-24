#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}


// begin of seg
struct lazy_seg{
public:
vector<ll>  st , lazy;
lazy_seg(int n){
	st.resize(4*n + 1 , 0) , lazy.resize(4*n + 1, 0);
}
lazy_seg() = default;
void push(int l , int r , int curr){
	if(lazy[curr] != 0){
		st[curr] += lazy[curr] ;
		if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
		lazy[curr] = 0 ;
	}
}
void pull(int l , int r , int curr){
	push(l,r,curr); int mid = l + (r-l)/2;
	if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
	st[curr] = max(st[2*curr] , st[2*curr+1]);
}
void upd(int x , int y, ll v,  int l, int r , int curr){
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
ll qry(int x , int y , int l , int r , int curr){
	int mid = (l+r)/2; push(l,r,curr);
	if(l == x && r == y) return st[curr];
	if(y <= mid) return qry(x,y,l,mid,2*curr);
	else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
	return max(qry(x,mid,l,mid,2*curr) , qry(mid+1,y,mid+1,r,2*curr+1));
}
void build(int l , int r,  int curr){
	int mid = (l+r)/2;
	if(l == r){
		st[curr] = 0; 
		return ;
	}
	build(l,mid,2*curr);
	build(mid+1,r,2*curr+1);
	st[curr] = max(st[2*curr] ,st[2*curr+1]);
}
};
// end
// se c == 1 , updates nos nós, caso contrario nas arestas
template <class T>
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
	void update_subtree(int x , T v){
		seg.upd(in[x] , out[x]-1 , v, 0 , n-1 , 1);
		return ;
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
	T query_path(int x , int y , bool c = 0){  
		int u = lca(x,y);
		T ans = - LLONG_MAX;
		for(; Hd[x] != Hd[y] ; y = p[Hd[y]]){
			if(in[Hd[x]] > in[Hd[y]]) swap(x,y);
			ans = max(ans , seg.qry(in[Hd[y]] , in[y] , 0, n-1, 1));
		}
		if(in[x] > in[y]) swap(x,y);
		if(in[u] + 1 - (c ? 1 : 0) <= in[y]) ans = max(ans ,seg.qry(in[u] + 1 - (c ? 1 : 0) , in[y],  0 , n-1, 1)); 
		return ans;
	}
	T query_subtree(int x){
		return seg.qry(in[x] , out[x]-1 , 0, n-1, 1);
	}

private:
	vector < vi > g; 
	vi Sz , Hd , in , out ,p ; 
	int n , edges =0  , tin = 0;
};

int32_t main(){
	int n ;
	cin >> n;
	HLD<ll> hld(n);
	rep(i,0,n-1){
		int x , y;
		cin >>x >> y;
		hld.add_edge(x,y);
	}
	hld.decompose(1);
	int q;
	cin >> q;
	while(q--){
		string s;
		cin >> s;
		if(s == "add"){
			int x , y;
			cin >> x >> y;
			hld.update_subtree(x,y);
		}
		else{
			int x , y;
			cin >> x >> y;
			cout << hld.query_path(x,y,1) << endl;
		}
	}
}