#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<int> vi;

template<class T> int sgn(T x){
	return (x > 0) - (x < 0);
}

template<class T> // cuidado naim!!
struct Point{
	typedef Point P;
	T x , y;
	explicit Point(T x = 0 , T y = 0) : x(x) , y(y){

	}
	bool operator <(P p) const{
		return tie(x,y) < tie(p.x , p.y);
	}
	bool operator==(P p)const{
		return tie(x,y) == tie(p.x , p.y);
	}
	P operator+(P p) const{
		return P(x + p.x , y + p.y);
	}
	P operator-(P p) const{
		return P(x - p.x , y - p.y);
	} 
	P operator*(T d) const{
		return P(x * d , y * d);
	}
	P operator/(T d) const{
		return P(x/d , y/d);
	}
	T dot(P p)const{
		return x*p.x + y*p.y;
	}
	T cross(P p) const{
		return x *p.y - y * p.x;
	}
	T cross(P a , P b) const{ 
		return (a - *this).cross(b - *this);
	}
	T dist2() const{
		return x*x + y*y;
	}
	double dist() const{
		return sqrt((double) dist2());
	}
	double angle() const{
		return atan2(y,x);
	}
	P unit() const{
		return *this / dist();
	}
	P perp() const {
		return P(-y , x);
	}
	P normal() const{
		return perp().unit();
	}
	P rotate(double a) const{
		return P(x * cos(a) - y*sin(a) , x*sin(a) + y*cos(a));
	}
	friend ostream& operator<<(ostream & os , P p){
		return os<< "(" << p.x <<", " << p.y <<")" ; 
	}
};

typedef Point<double> P;
const double EPS = 1e-9;
vector<P> convexHull(vector<P> pts){
	if(sz(pts) <= 1) return pts;
	P pivot = pts[0];
	rep(i,0,sz(pts)) pivot = min(pivot , pts[i]);
	sort(all(pts) , [&](P a , P b){
		a = a - pivot , b = b - pivot;
		int hp1 = a < P(0,0) , hp2 = b < P(0,0);
		if(hp1 != hp2) return hp1 < hp2;
		if(abs(a.cross(b)) > EPS){
			return a.cross(b) > -EPS;
		}
		return a.dist2() < b.dist2() + EPS;
	});
	vector<P> hull;
	rep(i,0,sz(pts)){
		while(hull.size() > 1 && ((hull.back() - hull[sz(hull) - 2]).cross(pts[i] - hull.back()) <= EPS)) hull.pop_back();
		hull.push_back(pts[i]);	
	}
	if(hull.back()== hull[0]) hull.pop_back();
	return hull;
}

template<class P>
pair<int, P> lineInter(P s1 , P e1 , P s2 , P e2){
	auto d = (e1 - s1).cross(e2 - s2);
	if(abs(d) <= EPS) return {-(s1.cross(e1,s2) == 0) , P(0,0)};
	auto p = s2.cross(e1,e2) , q = s2.cross(e2,s1);
	return {1 , (s1 * p + e1 * q) / d} ; 
}

double segDist(P& s,P& e,P& p){
	if(s==e)return (p-s).dist();
	auto d = (e-s).dist2(),t = min(d,max(0.0,(p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}



pair<P,int> getInter(P s,P e,vector<P>& p,int f){
	int n =sz(p);
	for(int i=1;i<n;i++){
		P a = p[i];
		P b = p[(i+1)%n];
		pair<int,P> inter = lineInter(s,e,a,b);
		
		if(inter.ff and segDist(a,b,inter.ss)<=EPS){
			if(f){
				return make_pair(inter.ss,i+1);
			}else{
				return make_pair(inter.ss,i);
			}

		}
	}

	assert(false);
	return make_pair(s,-1);
}

double polygonArea2(vector<P>& v) {
	double a = v.back().cross(v[0]);
	rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
	return abs(a);
}

const double PI = acos(-1);
void solve(){
	int n;
	cin>>n;
	vector<P> p(n);
	for(int i=0;i<n;i++){
		cin >> p[i].x>>p[i].y;
		//if(i!=0)p[i]=p[i] - p[0];
	}
	//p[0]=P(0,0);
	P A = p[0];
	P B = p[1];
	P AB = B - A;
	P dir1 = AB.rotate(PI/4.0); // 45 degrees
	P dir2 = AB.rotate(PI - PI/4.0);// 135 degrees
	P mid = (A + B)/2.0;

	auto inter1 = getInter(mid,mid + dir1,p,1);

	auto inter2 = getInter(mid,mid + dir2,p,0);

	vector<P> hull;
	P p1 = inter1.ff;
	P p2 = inter2.ff;

	if(p2.cross(p1,mid) > - EPS){
		swap(p1,p2);
		assert(false);
	}

	for(int i=0;i<n;i++){
		if(p2.cross(p1,p[i])>-EPS and mid.cross(p2,p[i]) < EPS and mid.cross(p1,p[i]) > -EPS){
			if((p[i]-p1).dist()<EPS or (p[i]-p2).dist()<EPS)continue;
			hull.pb(p[i]);
			//assert(i>=2);
		}
	}
	hull.pb(inter1.ff);
	hull.pb(inter2.ff);
	hull.pb(mid);
	
	hull = convexHull(hull);

	double area1 = polygonArea2(hull);
	double tot = polygonArea2(p);
	

	cout << setprecision(10) << fixed;
	double ans = abs(area1/tot); 
	cout << ans << endl;
}

int32_t main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}