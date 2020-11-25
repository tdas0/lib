// UPSOLVE
#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) ((int)v.size())
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll exp(ll b, ll e ,ll m) {
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return mod(ans,m);
}


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x=0, T y=0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
  bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  ld dist() const { return (ld)sqrt((ld)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this/dist(); } // makes dist()=1
  P perp() const { return P(-y, x); } // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

typedef Point<ll> P;

bool cmp(P a,P b){
    int hp1 = a < P(0,0) , hp2 = b < P(0,0);
    if(hp1 != hp2) return hp1 < hp2;
    if(a.cross(b) != 0){
      return a.cross(b)  > 0;
    }
    return a.dist2() < b.dist2();
}

ll area(P a,P b,P c){
  return abs(a.cross(b,c));
}

int32_t main(){
  fastio;
  int n;
  cin>>n;
  vector<P> v1(n),segs,v;
  rep(i,0,n)cin>>v1[i].x>>v1[i].y;
  rep(i,0,n)segs.pb(v1[(i+1)%n] - v1[i]);
  sort(all(segs),cmp);
  v.pb(P(0,0));
  // ordem dos segmentos nao importa!!!
  rep(i,0,n-1)v.pb(v.back() + segs[i]);
  
  ld ans = 1e18;
  
  auto nxt = [&](int j){
    if(j==n-1)return 0;
    return j+1;
  };
  int j = 1;
  rep(i,0,n){
    int nx = nxt(i);
    if(i==j)j=nxt(j);
    while(nxt(j)!=i and area(v[i],v[nx],v[nxt(j)]) >= area(v[i],v[nx],v[j]))j=nxt(j);
    ans=min(ans,area(v[i],v[nx],v[j])/(v[i]-v[nx]).dist());
  }
  cout<<setprecision(2)<<fixed;
  cout<<ans<<endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
