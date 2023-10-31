#include <bits/stdc++.h>
#define sz(v) ((int)v.size())
#define rep(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define pb push_back
#define ff first
#define ss second
#define endl '\n'
#define sz(v) ((int)v.size())
#define all(v) begin(v),end(v)
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

void dbg_out() { cerr << endl ;}
template<typename Head, typename... Tail> void dbg_out(Head H,Tail... T){
	cerr<<' '<<H ;
	dbg_out(T...);
}
#ifdef LOCAL
#define dbg(...) cerr<<"("<< #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__), cerr << endl;
#else 
#define dbg(...) 42
#endif

const int N = 300100;
vi g[N];

struct block{
	ll sum,tam,id,resp;
	block(ll v){
		sum = v;
		resp = v;
		tam = 1;
		id = v;
	}
	block(){
		sum = tam = id = resp = 0;
	}
	bool operator<(const block& o)const{
		if(sum * o.tam == o.sum * tam)return id < o.id;
		return sum * o.tam < o.sum * tam;
	}
};

int p[N];

int pai[N];
multiset<block> cand;
block curb[N];

int f(int x){return p[x]=(p[x]==x?x:f(p[x]));}
void join(int a,int b){
	a = f(a),b = f(b);
	cand.erase(curb[a]);
	if(pai[b]!=-1)cand.erase(curb[b]);
	curb[b].resp += curb[b].tam * curb[a].sum + curb[a].resp;
	curb[b].tam += curb[a].tam;
	curb[b].sum += curb[a].sum;
	curb[b].id = b;
	p[a] = b;
	if(pai[b]!=-1){
		cand.insert(curb[b]);
	}
}


void dfs(int v,int p = -1){
	pai[v] = p;
	curb[v] = block(v);
	if(p!=-1)cand.insert(curb[v]);
	for(auto to : g[v])if(to!=p)dfs(to,v);
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	int n,r;
	cin >> n >> r;
	rep(i,1,n){
		int a,b;
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(r);
	rep(i,1,n+1)p[i] = i;
	while(sz(cand) > 0){
		int id = cand.begin()->id;
		int p = pai[id];
		join(id,p);
	}
	cout << curb[f(1)].resp << endl;
}
