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

struct dsu{
	vi p , ps , sj;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1) , sj = vi(n+1,0);
		rep(i,0,n+1) p[i] = i;
	}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x] , sj[y] += sj[x];
		return 1;
	}
	void augment(int x){
		sj[find(x)] ++ ;
	}
};	

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

int n, m;
string s;
vi v;
bool mark[1000005];

ll p[1000005];

ll cur = 0;

ll ans = (ll) 1e18;
int sz;

ll get(int a, int b){
	ll soma = 0;
	if(b > sz){
		soma = p[sz] - p[a-1] + p[b -sz];
 	}
	else if(a < 1){
		soma = p[b] + p[sz] - p[sz + a -1];
	}
	else{
		soma = p[b] - p[a-1];
	}
	return soma;
}

int32_t main(){
	ios::sync_with_stdio(!cin.tie(0));
	cin >> n >> m;
	cin >> s;
	vi v(n);
	dsu T(2*m);
	rep(i,0,n) cin >> v[i] , T.augment(v[i]);
	s += s;
	SuffixArray sa(s);
	for(int i = 1; i < sz(sa.sa) ; i ++){
		if(sa.lcp[i] >= m && sa.sa[i] < m && sa.sa[i-1] < m)
			T.join(sa.sa[i] , sa.sa[i-1]);
	}
	for(int i = 0 ; i < m;  i ++){
		if(!mark[T.find(i)]){
			p[sz+1] = p[sz] + T.sj[T.find(i)] , mark[T.find(i)] = 1 ;
			sz++;
		}
	}
	for(int i = 1; i <= sz ; i ++){
		cur += (p[i] - p[i-1]) * (1ll * min(i-1, sz - i + 1));
	}
	ans = min(ans , cur);
	for(int i = 2 ; i <= sz ; i ++){
		int la = i - sz/2 , lb = i - 1;
		int lx = i , ly = i + sz/2 - 1;
		cur += get(la,lb) - get(lx,ly);
		ans = min(ans, cur);
	}
	printf("%lld\n" , ans);
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
