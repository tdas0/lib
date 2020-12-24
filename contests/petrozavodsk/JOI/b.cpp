// karen and cards
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

typedef array<int,3> ar;
typedef vector<int> vi;

struct node{
	ll mx = 0 , sum = 0;
	node(){
		mx = 0 , sum = 0;
	}
	node operator+(node &rhs){
		node p;
		p.mx = min(mx , rhs.mx);
		p.sum = sum + rhs.sum;
		return p;
	}
};

struct lazy_seg{
public:
	vector<node>  st ;
	vector<int> lazy;
	lazy_seg(int n){
		st.resize(4*n + 1 , node()) , lazy.resize(4*n + 1, 0);
	}
	lazy_seg() = default;
	void push(int l , int r , int curr){
		if(lazy[curr] != 0){
			st[curr].sum = (lazy[curr]*1ll)*((ll)r-l+1);
			st[curr].mx = lazy[curr];
 			if(l!=r) lazy[2*curr] = lazy[curr] , lazy[2*curr+1] = lazy[curr];
			lazy[curr] = 0 ;
		}
	}
	void pull(int l , int r , int curr){
		push(l,r,curr); int mid = l + (r-l)/2;
		if(l!=r) push(l,mid,2*curr) , push(mid+1,r,2*curr+1);
		st[curr] = (st[2*curr] + st[2*curr+1]);
	}
	void upd(int x , int y, ll v,  int l, int r , int curr){
		int mid = (l+r)/ 2;  push(l,r,curr);
		if(l == x && r == y){
			lazy[curr] = v;
			push(l,r,curr);
			return ;
		}
		if(y <= mid) upd(x,y,v,l,mid,2*curr);
		else if(x > mid) upd(x,y,v,mid+1,r,2*curr+1);
		else upd(x,mid,v,l,mid,2*curr) , upd(mid+1,y,v,mid+1,r,2*curr+1);
		pull(l,r,curr);
	}
	ll qry(int x , int y , int l , int r , int curr){
		int mid = (l+r)/2; push(l,r,curr);
		if(l == x && r == y) return st[curr].mx;
		if(y <= mid) return qry(x,y,l,mid,2*curr);
		else if(x > mid) return qry(x,y,mid+1,r,2*curr+1);
		return min(qry(x,mid,l,mid,2*curr) , qry(mid+1,y,mid+1,r,2*curr+1));
	}
};

vi c[3];

const int N = 500002;

vector<pair<int,int> > pt[N];

lazy_seg seg(N);

int32_t main(){
	int n;
	cin >> n;
	vi tot;
	for(int i = 1; i <= n; i ++){
		int x; char y;
		cin >> x >> y;
		if(y == 'R')
			c[0].push_back(x);
		else if(y == 'G')
			c[1].push_back(x);
		else if(y == 'B')
			c[2].push_back(x);
		tot.push_back(x);
	}
	sort(tot.begin() , tot.end());
	for(int i = 0 ; i < 3; i ++)
		sort(c[i].begin() , c[i].end());
	int mx = 0;
	for(int i = 0 ; i < tot.size() ; i ++){
		ar u = {0,0,0};
		for(int j = 0 ; j < 3; j ++)
			u[j] = upper_bound(c[j].begin() , c[j].end() , 2*tot[i] - 1) - lower_bound(c[j].begin() , c[j].end() , tot[i]);
		pt[u[0]].push_back({u[1], u[2] + 1});
		mx = max(mx , u[0]);
	}
	ll ans = 0;
	for(int i = mx; i >= 0 ; i --){
		for(auto w : pt[i]){
			int l = 0 , r = w.F;
			int ans = -1;
			while(l <= r){
				int mid = l + (r-l)/2;
				if(seg.qry(0,mid, 0, N-1, 1) <= (w.S))
					r = mid - 1,  ans = mid;
				else
					l = mid + 1;
			}
			if(ans != -1){
				seg.upd(ans,w.F,w.S,0,N-1,1);
			}
		}
		seg.qry(0,N-1,0,N-1,1);	
		ans += seg.st[1].sum;
	}
	cout << ans - 1 << endl;
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
