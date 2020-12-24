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
const int N = 3030;
vpl g[N];
struct edge{
	ll x , y, z;
}; 
int n , m , k;
vector<edge> v;
ll d[N];
void djikstra(){
	rep(i,1,n+1) d[i] = (ll) 1e18;
	priority_queue<pll , vpl, greater<pll> > pq;
	pq.push({0,1});
	while(!pq.empty()){
		pll u = pq.top();
		pq.pop();
		if(d[u.second] <= u.first) continue;
		d[u.second] = u.first;
		allin(w,g[u.second]){
			if(d[w.first] > u.first + w.second){
				pq.push({u.first+w.second, w.first});
			}
		}
	}
}

int32_t main(){
	cin >> n >> m >> k;
	rep(i,0,m){
		v.push_back({}) ; cin >> v[i].x >> v[i].y >> v[i].z;
		g[v[i].x].push_back({v[i].y , v[i].z});
		g[v[i].y].push_back({v[i].x , v[i].z});
	}
	djikstra();
	ll ans = d[n];
	rep(i,0,m){
		ll p = v[i].z;
		rep(j,1,n+1) g[j].clear();
		rep(j,0,m){
			g[v[j].x].push_back({v[j].y , max(0LL, v[j].z - p)});
			g[v[j].y].push_back({v[j].x , max(0LL, v[j].z - p)});
		}
		djikstra();
		ans = min(ans , d[n] + p * ((ll)k));	
	}
	cout << ans << endl;
}