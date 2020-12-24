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
const int N = 200005;
vi order , g[N] , g2[N];
int dg[N] , dp[N] , n , m , k , e[N];


int32_t main(){
	scanf("%d%d%d" , &n , &m , &k);
	set<int> miss;
	for(int i = 1; i <= k ;i ++)
		miss.insert(i);
	for(int i = 1 ; i <= n; i ++){
		scanf("%d" , &e[i]);
		miss.erase(e[i]);
	}	
	for(int i = 1; i <= m ; i ++){
		int x , y;
		scanf("%d%d" , &x , &y);
		g[y].push_back(x);
		g2[x].push_back(y);
		dg[x]++;
	}
	for(int i = 1; i <= n; i ++){
		if(!dg[i])
			order.push_back(i);
	}
	for(int i = 0 ; i < sz(order); i ++){
		auto v = order[i];
		for(auto w : g[v]){
			if(--dg[w] == 0)
				order.push_back(w);
		}
	}
	if(sz(order) != n){
		puts("-1");
		return 0;
	}
	reverse(all(order));
	vpi ord;
	for(int i = 0 ; i < sz(order) ; i ++){
		int has = k;
		auto v = order[i];
		for(auto w : g[v]){
			has = min(has, dp[w] - 1);
		}
		dp[v] = has;
		if(e[v]){
			if(dp[v] < e[v]){
				puts("-1");
				return 0;
			}
			dp[v] = e[v];
		}
		if(dp[v] < 1){
			puts("-1");
			return 0;
		}
		if(!e[v]){
			ord.push_back({dp[v] , v});
		}
	}
	cout << endl;
	sort(all(ord));
	for(auto w : ord){
		int la = 1;
		for(auto wk : g2[w.S]){
			la = max(la, e[wk] + 1);
		}
		auto fa = miss.lower_bound(la);
		if(fa == end(miss)){
			e[w.S] = w.F;
		}
		else{
			e[w.S] = min(w.F, *fa);
		}
		miss.erase(e[w.S]);
	}
	for(int i = 1; i <= n; i++){
		for(auto w : g2[i]){
			if(e[i] <= e[w]){
				puts("-1");
				return 0;
			}
		}
	}
	if(sz(miss)){
		puts("-1");
		return 0;
	}
	for(int i = 1; i <= n; i ++){
		printf("%d " , e[i]);
	}
	printf("\n");
}
