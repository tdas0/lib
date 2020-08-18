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
#define endl '\n'
#define pb push_back

const int N = 100100;
vi g[N];
int L[N];

struct DSU{
	vi pai,ps;
	vi tpai;
	vector<ll> val;
	DSU(){}
	DSU(int n){
		pai.resize(n+1);
		ps.resize(n+1);
		tpai.resize(n+1);
		val.resize(n+1);
		for(int i=1;i<=n;i++){
			ps[i] = 1;
			pai[i] = i;
			tpai[i] = i;
			val[i] = 0;
		}
	}
	int f(int x){
		return pai[x] = (pai[x]==x ? x : f(pai[x]));
	}
	int getps(int x){
		return ps[f(x)];
	}
	ll getV(int x){
		return val[f(x)];
	}
	bool join(int a,int b,ll novo){
		a = f(a),b = f(b);
		if(a==b)return 0;
		if(ps[a] > ps[b])swap(a,b);
		ps[b]+=ps[a];
		val[b]+=val[a]+novo;
		pai[a] = b;
		tpai[b] = (L[tpai[a]] < L[tpai[b]] ? tpai[a] : tpai[b]); 
		return 1;
	}
};
DSU dsu1,dsu2;
int pai[N];
void dfs(int v,int p = -1){
	for(int to : g[v])if(to!=p){
		pai[to] = v;
		L[to] = L[v] + 1;
		dfs(to,v);
	}
}


struct edge{
	int a,b,c,d,w;
	edge(){}
	edge(int a,int b,int c,int d,int w):a(a),b(b),c(c),d(d){}
}e[N];
ll ans = 0;


void join(int a,int b,ll w){
	while(a!=b){
		a = dsu1.f(a);
		a = dsu1.tpai[a];
		b = dsu1.f(b);
		b = dsu1.tpai[b];
		if(L[a] < L[b])swap(a,b);
		if(a==b)break;
		// a-> pai[a]:
		if(dsu2.join(a,pai[a],w)){
			ans+=w;
		}
		
		dsu1.join(a,pai[a],0);
	}
}
void join2(int a,int c,ll w){
	if(dsu2.join(a,c,w)){
		ans+=w;
	}
}

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;
	cin >> n >> m;
	dsu1 = DSU(n);
	dsu2 = DSU(n);
	for(int i=0;i<n-1;i++){
		int a,b;
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1);
	for(int i=0;i<m;i++){
		cin >> e[i].a >> e[i].b >> e[i].c >> e[i].d >> e[i].w;
	}
	sort(e,e+m,[&](edge a,edge b){
		return a.w < b.w;
	});
	

	for(int i=0;i<m;i++){
		join(e[i].a,e[i].b,e[i].w);
		join(e[i].c,e[i].d,e[i].w);
		join2(e[i].a,e[i].c,e[i].w);
	}
	cout << dsu2.getps(1) <<" "<<dsu2.getV(1) << endl;

}
