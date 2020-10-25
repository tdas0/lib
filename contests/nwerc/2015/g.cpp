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
int n, a[N];
pii pos[N];

#define ff first
#define ss second
#define pb push_back


template<class T, int SZ> struct OffBIT2D { 
  bool mode = 0; // mode = 1 -> initialized
  vector<pii> todo; // locations of updates to process
  int cnt[SZ], st[SZ];
  vi val; vector<T> bit; // store all BITs in single vector
  void init() { assert(!mode); mode = 1;
    int lst[SZ]; rep(i,0,SZ) lst[i] = cnt[i] = 0;
    sort(all(todo),[](const pii& a, const pii& b) { 
      return a.ss < b.ss; });
    trav(t,todo) for (int x = t.ff; x < SZ; x += x&-x) 
      if (lst[x] != t.ss) lst[x] = t.ss, cnt[x] ++;
    int sum = 0; rep(i,0,SZ) lst[i] = 0, st[i] = (sum += cnt[i]);
    val.resize(sum); bit.resize(sum); reverse(all(todo));
    trav(t,todo) for (int x = t.ff; x < SZ; x += x&-x) 
      if (lst[x] != t.ss) lst[x] = t.ss, val[--st[x]] = t.ss;
  }
  int rank(int y, int l, int r) {
    return upper_bound(begin(val)+l,begin(val)+r,y)-begin(val)-l; }
  void UPD(int x, int y, T t) {
    for (y = rank(y,st[x],st[x]+cnt[x]); y <= cnt[x]; y += y&-y) 
      bit[st[x]+y-1] += t; }
  void upd(int x, int y, T t) { 
    if (!mode) todo.pb({x,y});
    else for (;x<SZ;x+=x&-x) UPD(x,y,t); }
  int QUERY(int x, int y) { T res = 0;
    for (y = rank(y,st[x],st[x]+cnt[x]); y; y -= y&-y) res += bit[st[x]+y-1];
    return res; }
  T query(int x, int y) { assert(mode);
    T res = 0; for (;x;x-=x&-x) res += QUERY(x,y);
    return res; }
  T query(int xl, int xr, int yl, int yr) { 
    return query(xr,yr)-query(xl-1,yr)
      -query(xr,yl-1)+query(xl-1,yl-1); }
};

int32_t main(){
	scanf("%d" , &n);
	for(int i = 1; i <= n; i ++){
		int x;
		scanf("%d" , &x);
		a[x] = i;	
	}
	for(int i = 1; i <= n; i ++){
		int x;
		scanf("%d" , &x);
		pos[a[x]].F = i;
	}
	for(int i = 1; i <= n; i ++){
		int x;
		scanf("%d" , &x);
		pos[a[x]].S = i;
	}
	ll ans = 0;
	OffBIT2D<ll,N> bit;
	for(int i = 1; i <= n; i ++){
		bit.upd(pos[i].F,pos[i].S,+1);
	}
	bit.init();
	for(int i = 1; i <= n; i ++){
		ans += bit.query(pos[i].F,pos[i].S);
		bit.upd(pos[i].F,pos[i].S,+1);
	}
	printf("%lld\n" , ans);
}
