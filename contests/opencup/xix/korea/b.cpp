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

int n , m;
string s[55];
int l[55][55] , r[55][55] , ct = 0;
vi g[101 * 101];
bitset<101*101>  vis[101*101];
void dfs(int x ,int y){
	vis[y][x] = 1;
	for(auto w : g[x]){
		if(!vis[y][w]) dfs(w,y);
	}
}

struct TwoSat {
	int N;
	vector<vi> gr;
	vi values; // 0 = false, 1 = true
	TwoSat(int n = 0)
	{
		N = n;
		gr.clear(),gr.resize(2*n);
		values.clear(),values.resize(2*n);
	}
	int add_var() { // (optional)
		gr.emplace_back();
		gr.emplace_back();
		return N++;
	}
	void either(int f, int j) {
		f = max(2*f, -1-2*f);
		j = max(2*j, -1-2*j);
		gr[f].push_back(j^1);
		gr[j].push_back(f^1);
	}
	void set_value(int x) { either(x, x); }
	void at_most_one(const vi& li) { // (optional)
		if (sz(li) <= 1) return;
		int cur = ~li[0];
		rep(i,2,sz(li)) {
			int next = add_var();
			either(cur, ~li[i]);
			either(cur, next);
			either(~li[i], next);
			cur = ~next;
		}
		either(cur, ~li[1]);
	}
	void xor1(int a, int b){	// Exatamente um dos dois eh verdadeiro
		either(a, b);
		either(~a, ~b);
	}
	void xor0(int a, int b){	//Ambos sao falsos, ou ambos verdadeiros
		either(a, ~b);
		either(~a, b);
	}
	vi val, comp, z; int time = 0;
	int dfs(int i){
		int low = val[i] = ++time, x; z.push_back(i);
		trav(e, gr[i]) if (!comp[e])
			low = min(low, val[e] ?: dfs(e));
		if (low == val[i]) do {
			x = z.back(); z.pop_back();
			comp[x] = low;
			if (values[x>>1] == -1)
				values[x>>1] = x&1;
		} while (x != i);
		return val[i] = low;
	}
	bool solve(){
		values.assign(N, -1);
		val.assign(2*N, 0); comp = val;
		rep(i,0,2*N) if (!comp[i]) dfs(i);
		rep(i,0,N) if (comp[2*i] == comp[2*i+1]) return 0;
		return 1;
	}
};

int32_t main(){
	cin >> n >> m;
	pii bg;
	for(int i = 0 ;i < n ;i ++) cin >> s[i];
	for(int i = 0 ; i < n; i ++){
		ct ++ ;
		for(int j = 0 ; j < m ; j ++){
			if(s[i][j] == 'O') bg = pii(i,j);
			if(s[i][j] != '#'){
				l[i][j] = ct;
			}
			else ct ++ ;
		}
	}
	for(int j = 0 ; j < m ; j ++){
		ct ++ ;
		for(int i = 0 ; i < n; i ++){
			if(s[i][j] != '#'){
				r[i][j] = ct;
			} 
			else ct ++ ;
		}
	}
	for(int i = 0 ; i < n; i ++){
		for(int j = 0 ; j < m ; j ++){
			if(j && s[i][j] != '#' && s[i][j-1] == '#'){
				g[l[i][j]].push_back(r[i][j]);
			}
			if((j+1) < m && s[i][j] != '#' && s[i][j+1] == '#'){
				g[l[i][j]].push_back(r[i][j]);
			}
			if(i && s[i][j] != '#' && s[i-1][j] == '#'){
				g[r[i][j]].push_back(l[i][j]);
			} 
			if((i+1) < n && s[i][j] != '#' && s[i+1][j] == '#'){
				g[r[i][j]].push_back(l[i][j]);
			}
			if(j == 0 && s[i][j] != '#'){
				g[l[i][j]].push_back(r[i][j]);
			}
			if(j == (m - 1) && s[i][j] != '#'){
				g[l[i][j]].push_back(r[i][j]);	
			}
			if(i == 0 && s[i][j] != '#'){
				g[r[i][j]].push_back(l[i][j]);
			}
			if(i == (n - 1)&& s[i][j] != '#'){
				g[r[i][j]].push_back(l[i][j]);	
			}			
		}
	}
	for(int i = 1 ; i <= ct ; i ++){
		dfs(i,i);
	}
	TwoSat sat(ct + 2);
	
	for(int i = 0 ; i < n; i ++){
		for(int j = 0 ; j < m ; j++){
			if(s[i][j] == '*' || s[i][j] == 'O'){
				sat.at_most_one({~l[i][j] , ~r[i][j]});
			}
			int aa = l[i][j] , bb = r[i][j];
			if(!vis[l[bg.F][bg.S]][aa] && !vis[r[bg.F][bg.S]][aa]){
				sat.set_value(~aa);
			}
			if(!vis[r[bg.F][bg.S]][bb] && !vis[l[bg.F][bg.S]][bb]){
				sat.set_value(~bb);
			}
		}
	}
	for(int i = 1; i <= ct ;i ++){
		for(int j = i+1; j <= ct ;j ++){
			if(!vis[i][j] && !vis[j][i]){
				sat.at_most_one({i,j});
 			}
		}
	}
	cout << (sat.solve() ? "YES" : "NO") << endl;
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/