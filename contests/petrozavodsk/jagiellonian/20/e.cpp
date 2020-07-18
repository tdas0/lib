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

const int N = 1000005;

struct event{
	int type;
	int yb, ye, xa , xb;
	int id;
}; 
vector<event> e;
int n , q;
template<class T = ll>
struct ST{
	vector<T> st; int n; 
	T ini; 
	ST(int n , T ini = -LLONG_MAX) : st(2*n , ini) , n(n) , ini(ini) {}
	void upd(int pos, T val){
		ll p = max(val, st[pos + n]);
		for(st[pos += n] = p ; pos /= 2;)
			st[pos] = max(st[2*pos] , st[2*pos + 1]);
	}
	T query(int x , int y){ 
		T ra = ini , rb = ini;
		for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
			if(x&1) ra = max(ra , st[x]) , x++;
			if(y&1) --y , rb = max(st[y] , rb);
		}
		return max(ra , rb);
	}
};
bool ok[N];
int32_t main(){
	scanf("%d%d" , &n , &q);
	vi tocmp;
	for(int i = 0 ; i < n ; i++){
		int x , y, r;
		scanf("%d%d%d" , &x , &y , &r);
		tocmp.push_back(x);
		e.push_back({0 , min(y-r , y+r) , max(y + r , y-r), x , x, i});
	}
	for(int i = 0 ;  i < q ; i ++){
		int px , py , qx , qy, ymin , ymax;
		scanf("%d%d%d%d%d%d" , &px,  &py, &qx, &qy , &ymin , &ymax);
		if(px > qx) swap(px, qx);
		if(ymin > ymax) swap(ymin , ymax);
		e.push_back({1,ymin,ymax,px,qx,i});
		tocmp.push_back(px);
		tocmp.push_back(qx);
	}
	sort(all(tocmp));
	tocmp.resize(unique(all(tocmp)) - begin(tocmp));
	sort(all(e) , [&](event a , event b){
		return pii(a.yb , a.type) < pii(b.yb , b.type);
	});
	ST seg(sz(tocmp) + 30);
	for(auto w : e){
		if(w.type == 0){
			seg.upd(lower_bound(all(tocmp) , w.xa)  - begin(tocmp),w.ye);
		}
		else{
			int L = lower_bound(all(tocmp) , w.xa) - begin(tocmp) , R =  lower_bound(all(tocmp) , w.xb)  - begin(tocmp);
			ok[w.id] = (seg.query(min(L,R) , max(L,R)) < w.ye); 
		}
	}
	for(int i = 0 ; i < q; i ++){
		if(ok[i]) printf("YES\n");
		else printf("NO\n");
	}
}



