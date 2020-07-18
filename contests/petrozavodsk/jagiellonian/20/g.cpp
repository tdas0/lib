#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define pb push_back
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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point{
	typedef Point P;
	T x,y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	T cross(P p)const{return x*p.y - y * p.x;}
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
};

typedef Point<ll> P;

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> bool segInter(P a,P b,P c,P d){
	auto oa = c.cross(d,a),ob = c.cross(d,b),
		oc = a.cross(b,c),od = a.cross(b,d);
		if(sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0){
			return true;
		}
		if(onSegment(c,d,a))return 1;
		if(onSegment(c,d,b))return 1;
		if(onSegment(a,b,c))return 1;
		if(onSegment(a,b,d))return 1;
		return 0;
}


void solve(){

	int n;
	cin>>n;
	vector<P> ini(n),fim(n);

	for(int i=0;i<n;i++){
		cin >> ini[i].x>>ini[i].y;
	}
	for(int i=0;i<n;i++){
		cin >> fim[i].x>>fim[i].y;
	}

	vector<int> vec;
	for(int i=0;i<n;i++){
		vec.pb(i);
	}
	do{
		vector<pair<P,P>> segs;
		int Good=1;
		for(int i=0;i<n;i++){
			int cur = vec[i];
			int ok = 1;
			for(auto it : segs){
				if(segInter(it.F,it.S,ini[cur],fim[i]))ok=0;
			}
			if(ok){
				segs.pb({ini[cur],fim[i]});
			}else Good = 0;
		}
		if(Good){
			for(int i=0;i<n;i++){
				int cur = vec[i];
				cout << 2 << endl;
				cout << ini[cur].x<<" "<<ini[cur].y << endl;
				cout << fim[i].x<<" "<<fim[i].y << endl;
			}
			return ;
		}

	}while(next_permutation(all(vec)));


}

int main(){

	int t;
	cin>>t;
	while(t--){
		solve();
	}

}