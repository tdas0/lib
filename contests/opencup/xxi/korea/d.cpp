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
typedef array<int,3> ar;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
const int N = 300005;
int n, m , pai[N] , peso[N] , up[N];

int fd(int x){
	return pai[x] == x ? x : fd(pai[x]);
}

int dep(int x){
	int cur = x;
	int depth = 0;
	int fdc = fd(cur);
	while(cur != fdc){
		depth++;
		cur = pai[cur];
	}
	return depth;
}

void join(int u , int v , int z){
	u = fd(u) , v = fd(v);
	if(peso[u] > peso[v])
		swap(u,v);
	up[u] = z;
	pai[u] = v;
	peso[v] += peso[u];
}

ll get(int x , int y){
	int dx = dep(x) , dy = dep(y);
	ll ans = (ll) 1e18;
	while(x != y){
		if(dx < dy){
			swap(dx,dy);
			swap(x,y);
		}
		ans = min(ans, 1ll*up[x]);
		x = pai[x];
		dx--;
	}
	return ans;
}

int32_t main(){
	scanf("%d%d" ,&n, &m);
	for(int i = 1; i <= n; i ++)
		peso[i] = 1 , pai[i] = i;
	vector< array<int,3> > e;
	for(int i = 0 ; i < m ; i ++){
		e.push_back(ar());
		scanf("%d%d%d" , &e.back()[0] , &e.back()[1] , &e.back()[2]);
	}
	sort(all(e), [&](ar x , ar y){
		return x[2] > y[2];
	});
	ll ans = 0;
	for(int i = 0 ; i < m ; i ++){
		auto [x,y,z] = e[i];
		if(fd(x) == fd(y)){
			if(get(x,y) != z){
				puts("-1");
				return 0;
			}
		}
		else{	
			ans += ((ll)(1ll*peso[fd(x)])*(1ll*peso[fd(y)])) * (1ll * z);
			join(x,y,z);
		}
	}
	ll x2 = 0 , xs = 0;
	set<int> jf;
	for(int i = 1; i <= n; i ++){
		if(!jf.count(fd(i))){
			x2 += (1ll * peso[fd(i)]) * (1ll * peso[fd(i)]);
			xs += peso[fd(i)];
			jf.insert(fd(i));
		}
	}
	ans += (xs * xs - x2) / 2ll;
	printf("%lld\n" , ans);
}
