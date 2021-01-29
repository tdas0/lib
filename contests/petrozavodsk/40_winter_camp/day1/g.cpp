#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int) (x).size()
#define ll long long
#define F first
#define S second
typedef vector<int> vi;
typedef pair<int,int> pii;
// begin of 2cc
const ll mod = (ll) 1e9 + 7;
const int N = 300005;
vi num, st, comps;
vector<vector<pii>> ed;
int Time;
ll pot[N] , dp[N][2];
bool vis[N];
vector<pii> edges;
int jf[N][2];
int ct = 0 , tam = 0;
void f(vi x){
	for(auto w : x)
		vis[edges[w].first] = true, vis[edges[w].second] = true;
	comps.push_back(sz(x));
}

int dfs(int at, int par){
	int me = num[at] = ++Time, e , y, top = me;
	for (auto pa : ed[at]) if(pa.second != par){
		tie(y,e) = pa;
		if(num[y]){
			top = min(top, num[y]);
			if(num[y] < me)
				st.push_back(e);
		}	else {
			int si = sz(st);
			int up = dfs(y,e);
			top = min(top,up);
			if(up == me){
				st.push_back(e);
				f(vi(st.begin() + si , st.end()));
				st.resize(si);
			}
			else if(up < me) st.push_back(e);
		}
	}
	return top;
}

void bicomps(){
	num.assign(sz(ed) , 0);
	for(int i = 0 ; i < sz(ed); i ++)	
		if(!num[i])
			dfs(i,-1);
}


void clear(int n){
	ed.clear() , num.clear() , st.clear(), comps.clear() , edges.clear();
	Time = 0;
	for(int i = 0 ; i < n; i ++)
		vis[i] = false;
}

int n , m; ll k;
ll computa(int x , int y){
	if(x == tam){
		if(y)
			return k - 1;
		else
			return k - 2;
	}
	if(jf[x][y] == ct)
		return dp[x][y];
	jf[x][y] = ct;
	if(y)
		return dp[x][y] = (computa(x+1,0) * (k-1))%mod;
	else
		return dp[x][y] = (computa(x+1,1) + computa(x+1,0)*(k-2)) % mod;
}

ll solve(){
	scanf("%d%d%lld" , &n, &m , &k);
	pot[0] = 1;
	for(int i = 1; i <= n ; i ++)
		pot[i] = pot[i-1] * (k-1) % mod;
	ed.resize(n);
	for(int i = 0 ; i < m ; i ++){
		int x, y;
		scanf("%d%d" , &x, &y);
		x-- , y--;
		edges.push_back({x,y});
		ed[x].push_back({y,i});
		ed[y].push_back({x,i});
	}
	bicomps();
	for(int i = 0 ; i < n; i ++)
		if(!vis[i])
			comps.push_back(1);
	ll ans = 1;
	for(int i = 0 ; i < sz(comps); i ++){
		ll inner = (i ? 1 : 0);
		if(comps[i] > 1){
			++ct , tam = comps[i];
			ans = (ans * (k - inner)) % mod;
			ans = (ans * computa(2,1)) % mod;
		}
		else{
			ans = (ans * (k-inner)) % mod;
		}
	}
	clear(n);
	return ans;
}

int32_t main(){
	int  t;
	scanf("%d" , &t);
	for(int _ = 0 ; _ < t ; _ ++){
		printf("%lld\n" , solve());
	}
}
