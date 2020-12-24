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

template <class T> 
struct lazy_seg{
public:
	vector<T>  st , lazy;
	lazy_seg(int n){
		st.resize(4*n + 1 , 0) , lazy.resize(4*n + 1, 0);
	}
	lazy_seg() = default;
	void push(int l , int r , int curr){
		if(lazy[curr] != 0){
			st[curr] += lazy[curr]*(r-l+1);
			if(l!=r) lazy[2*curr] += lazy[curr] , lazy[2*curr+1] += lazy[curr];
			lazy[curr] = 0 ;
		}
	}
	void pull(int l , int r , int curr){
		push(l,r,curr); int mid = l + (r-l)/2;
		if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
		st[curr] = (st[2*curr] + st[2*curr+1]);
	}
	void upd(int x , int y, T v,  int l, int r , int curr){
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
	T qry(int x , int y , int l , int r , int curr){
		int mid = (l+r)/2; push(l,r,curr);
		if(l == x && r == y) return st[curr];
		if(y <= mid) return qry(x,y,l,mid,2*curr);
		else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
		return (qry(x,mid,l,mid,2*curr) + qry(mid+1,y,mid+1,r,2*curr+1));
	}
	void build(int l , int r,  int curr){
		int mid = (l+r)/2;
		if(l == r){
			st[curr] = 0; 
			return ;
		}
		build(l,mid,2*curr);
		build(mid+1,r,2*curr+1);
		st[curr] = (st[2*curr]  + st[2*curr+1]);
	}
};

const int N = 100005;
vi g[N];
int n , m , a[N] , ans[N];
lazy_seg<ll> seg(N);
vpi has[N];

void dfs(int x , int p = -1){
	for(auto w : has[x]){
		seg.upd(w.F,w.S,1,0,N-1,1);
	}
	ans[x] += seg.qry(a[x],a[x],0,N-1,1);
	for(auto w : g[x]){
		if(p == w)
			continue;
		dfs(w,x);
	}
	for(auto w : has[x]){
		seg.upd(w.F,w.S,-1,0,N-1,1);
	}
}
int go[N][22];

void dfs_lift(int x , int p = -1){
	go[x][0] = p;
	for(int j = 1; j < 22; j ++){
		if(go[x][j-1] != -1)
			go[x][j] = go[go[x][j-1]][j-1];
	}
	for(auto w : g[x]){
		if(w != p)
			dfs_lift(w,x);
	}
}

int32_t main(){
	scanf("%d%d" , &n , &m);
	for(int i = 0 ; i < N ; i ++){
		for(int j = 0 ; j < 22; j ++){
			go[i][j] = -1;
		}
	}
	for(int i = 1; i <= n ; i++){
		int p;
		scanf("%d%d" , &a[i] , &p);
		if(p != i)
			g[p].push_back(i) , g[i].push_back(p);
	}
	dfs_lift(1);
	for(int i = 0 ; i < m ;i ++){
		int o , l ,r;
		scanf("%d%d%d" , &o , &l , &r);
		for(int j = 21; j >= 0 ; j --){
			if(go[o][j] != -1 && a[go[o][j]] <= r)
				o = go[o][j];
		}
		has[o].push_back({l,r});
	}
	dfs(1);
	for(int i = 1; i <= n; i ++){
		printf("%d " , ans[i]);
	}
	printf("\n");
}