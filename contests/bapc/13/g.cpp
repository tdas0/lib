#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
struct circle{
	double x, y;
	double radi;
}; 

struct dsu{
	vi p , ps;
	dsu(int n){
		p = vi(n+1),ps = vi(n+1,1);
		rep(i,0,n+1) p[i] = i;
	}
	int find(int x){
		return p[x] = (p[x]==x?x:find(p[x]));
	}
	bool join(int x , int y){
		x = find(x) , y = find(y);
		if(x == y) return 0;
		if(ps[x] > ps[y]) swap(x,y);
		p[x] = y, ps[y] += ps[x];
		return 1;
	}
};	

const double EPS = 1e-8;
bool intersect(circle a , circle b){
	double u = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
	double v = (a.radi + b.radi) * (a.radi + b.radi);
	if(u + EPS <= v) return true;
	return false;
}
int n,w;
bool ok(double mid,vector<circle> &v){
	dsu T(n + 3);
			int c1 = n  , c2 = n+1;
			vector<circle> u = v;
			for(int j = 0 ; j < n;  j++) u[j].radi += mid;
			for(int i = 0 ; i < n; i ++){
				double uv = u[i].x - u[i].radi;
				double vv = u[i].x + u[i].radi;
				if(uv - EPS - mid <= 0.000) {
					T.join(c1, i);
				}
				if(w*1.000 - mid + EPS <= vv){ 
					T.join(c2,i);
				}
				for(int j = i+1 ; j < n; j ++){
					if(intersect(u[i] , u[j])){
						T.join(i, j);
					}
				}	
			}
			bool aa = true;
		
			if(T.find(c1) == T.find(c2)) aa = false;

	return aa;
}

int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--){
		cin >> w >> n;
		vector<circle> v(n);
		for(int i = 0 ; i< n; i ++){
			cin >> v[i].x >> v[i].y >> v[i].radi;
		}
		double l = 0.0000 , r = (double)((1.0*w)/2.0);

		for(int it = 0 ;  it < 130 ; it ++){
			double mid = (l+r)/2.0;

			if(ok(mid,v)){
				l = mid;
			}
			else r = mid;
		}
		cout << setprecision(10) << fixed;
		cout << (l) << endl;
	}
}