#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
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
#define int long long


const int N = 620;

int x[N],y[N];


double dp[N][N][2];
int vis[N][N][2];
vi g[N];
int ct=0;

ll sq(ll x){
	return x*x;
}

double dist(int i,int j){
	return sqrt(sq(x[i] - x[j]) + sq(y[i] - y[j]));
}

double solve(int l,int r,int f){
	if(vis[l][r][f]==ct)return dp[l][r][f];
	if(l>=r)return 0;
	vis[l][r][f] = ct;
	double & x=  dp[l][r][f];
	x=0;
	int cur = (f ? r : l);
	for(int to : g[cur]){
		if(l<to and to<r){
			x = max(x,dist(cur,to) + max(solve(l,to,1),solve(to,r,0)));
		}
	}
	return x;
}


void addEdge(int a,int b){
	g[a].pb(b);
	g[b].pb(a);
}

void QUERY(){
	// LEMBRAR DE ZERAR
	int n;
	cin>>n;
	ct++;

	for(int i=1;i<=n;i++){
		cin >> x[i] >> y[i];
		x[i+n] = x[i];
		y[i+n] = y[i];
	}
	
	for(int i=1;i<=2*n;i++){
		g[i].clear();
	}
	
	int m;
	cin>>m;

	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		addEdge(u,v);
		addEdge(u,v+n);
		addEdge(u+n,v);
		addEdge(u+n,v+n);
	}


	double res = 0;
	for(int i=1;i<=n;i++){
		res = max(res,max(solve(i,i+n,1),solve(i,i+n,0)));
	}
	cout << setprecision(10) << fixed;
	cout << res << endl;

}

int32_t main(){
	int t;
	cin>>t;
	while(t--){
		QUERY();
	}
}