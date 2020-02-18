#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
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
int dist[1010][1010];
struct gas{ll x , cost;};
struct node{ll x , fuel;};
vpl grafo[1010] , g[4*120*120];
vector<node > v;
vector<gas> opt;
set<int> possible[4*120*120];
int source,  sink;
ll d[4*120*120];
int idx[122][100005];
int t;
void dijkstra(int x){
	dist[x][x] = 0;
	priority_queue<pii , vector<pii> , greater<pii> > pq;
	pq.push({0,x});
	while(!pq.empty()){
		pii u = pq.top(); pq.pop();
		if(dist[x][u.second] < u.first) continue;
		for(auto w : grafo[u.second]){
			if(dist[x][w.first] > u.first + w.second && (u.first + w.second) <= t){
				dist[x][w.first] = u.first + w.second;
				pq.push({dist[x][w.first] , w.first});
			}
		} 
	}
}

int getint(){
	char c='-';
	int a = 0;
	while(!(c>='0' && c<='9')) c= getchar();
	while(c>='0' && c <= '9') a = (10*a+ (c-'0')) , c = getchar();
	return a;
}

void solve(){
	int n =getint(), m = getint() , s = getint();
	v.clear() ; opt.clear() ; 
	t =getint();
	rep(i,0,n+1){
		grafo[i].clear();
	}
	rep(i,0,m){
		ll x, y , z;
		x = getint() , y = getint() , z = getint();
		grafo[x].push_back({y,z});
		grafo[y].push_back({x,z});
	}
	rep(i,0,s){
		ll x , y;
		x = getint() , y = getint();
		opt.push_back({x,y});
	}
	source = getint() , sink = getint();
	opt.push_back({sink, 0});
	s = sz(opt);
	rep(i,0,s){
		dijkstra(opt[i].x);
	}
	rep(i,0,s){
		rep(j,0,s){
			if(i == j) continue;
			if(dist[opt[i].x][opt[j].x] <= t){
				if(opt[j].cost <= opt[i].cost){
					possible[opt[j].x].insert(0);
					possible[opt[i].x].insert(dist[opt[i].x][opt[j].x]);
				}
				else{
					possible[opt[j].x].insert(t - dist[opt[i].x][opt[j].x]);
					possible[opt[i].x].insert(t);
				}
			}
		}
	}
	ll ct = 0;
	ll final = 0;
	ll start = 0;
	possible[source].insert(0);
	rep(i,0,s){
		int last = -1;
		ll cls = 0;
		for(auto w : possible[opt[i].x]){
			if(w > t) continue;
			v.push_back({opt[i].x , w}); 
			idx[i][w] = ++ct; 
			if(last != -1) g[last].push_back({idx[i][w] , (w - cls)*opt[i].cost}); 
			last = idx[i][w] , cls = w;
		}
		if(opt[i].x == source) start = idx[i][0];
		if(opt[i].x == sink) final = idx[i][0];
	}
	rep(i,0,s){
		rep(j,0,s){
			if(i == j) continue;
			if(dist[opt[i].x][opt[j].x] <= t){
				if(opt[j].cost <= opt[i].cost){
					g[idx[i][dist[opt[i].x][opt[j].x]]].push_back({idx[j][0] , 0 });
				}
				else{
					g[idx[i][t]].push_back({idx[j][t-dist[opt[i].x][opt[j].x]] , 0});
				}
			}
		}
	}
	priority_queue<pll, vector<pll> , greater<pll> > pq;
	pq.push({0, start });
	while(!pq.empty()){
		pll u = pq.top();
		pq.pop();
		if(u.first >= d[u.second]) continue;
		if(u.second == final){
			printf("%lld\n" , u.first);
			break ; 
		}
		d[u.second] = u.first;
		for(auto w : g[u.second]){
			if(d[w.first] > w.second + u.first){
				pq.push({w.second + u.first , w.first});
			} 
		}
	}
	rep(i,0,n+1){
		rep(j,0,s){
			dist[opt[j].x][i] = (int) 1e9;
		}
	}
	rep(i,0,ct+1) d[i] = (ll) 1e18 , g[i].clear();
	return ; 
} 

int32_t main(){
	rep(i,0,4*120*120) d[i] = (ll) 1e18;
	rep(i,0,1010){
		rep(j,0,1010){
			dist[i][j] = (int) 1e9;
		}
	}
	int T = getint();
	while(T--) solve();	
}