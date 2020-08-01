#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
const int N = 200005;
set<int> g[N];

int32_t main(){
	int n , m ;
	cin >> n >> m;
	for(int i = 0 ; i <m  ; i ++){
		int x , y;
		cin >> x >> y;
		g[x].insert(y);
		g[y].insert(x);
	}
	queue<int> q;
	for(int i = 1 ; i <= n; i ++) if(sz(g[i]) == 2) q.push(i);
	while(sz(q)){
		int u = q.front();
		q.pop();
		if(sz(g[u]) != 2) continue;
		int a = *begin(g[u]) , b = *next(begin(g[u]));
		g[u].clear();
		g[a].erase(u) , g[b].erase(u);
		g[a].insert(b) , g[b].insert(a);
		if(sz(g[a]) == 2) q.push(a);
		if(sz(g[b]) == 2) q.push(b);
	}
	vi has;
	for(int i = 1; i <= n; i ++){
		if(sz(g[i]) > 1){
			cout << "No" << endl;
			return 0;
		}
		else{
			if(sz(g[i]) == 1) has.push_back(i);
		}
	}
	if(sz(has) == 2 && g[has[0]].count(has[1]) && g[has[1]].count(has[0])){
		cout <<"Yes" << endl;
	}
	else{
		cout <<"No" << endl;
	}
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/