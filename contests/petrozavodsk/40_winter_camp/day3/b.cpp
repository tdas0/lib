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
//#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
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
};
typedef Point<double> PT;

struct L {
    PT a, b;
    double ang;
    L(){}
    L(PT a, PT b) : a(a), b(b) {}
};

double angle (L la) { return atan2(-(la.a.y - la.b.y), la.b.x - la.a.x); }

const double inf = 1e100, eps = 1e-9;
const double PI = acos(-1.0L);

int cmp (double a, double b = 0) {
  if (abs(a-b) < eps) return 0;
  return (a < b) ? -1 : +1;
}


bool comp (L la, L lb) {       
    if (cmp(la.ang, lb.ang) == 0) return (lb.b - lb.a).cross(la.b - lb.a) > eps;
    return cmp(la.ang,lb.ang) < 0;
}


typedef Point<double> P;
pair<int, PT> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0) // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}


pair<int, PT> lineInter(L la,L lb){
  return lineInter(la.a,la.b,lb.a,lb.b);
}


bool check (L la, L lb, L lc) {
    PT p = lineInter(lb, lc).ss;
    double det = (la.b - la.a).cross(p - la.a);
    return cmp(det) < 0;
}
template<class T>
T polygonArea2(vector<Point<T>>& v) {
  T a = v.back().cross(v[0]);
  rep(i,0,sz(v)-1) a += v[i].cross(v[i+1]);
  return a;
}
const int N = 500100;
int dq[2*N];
int idl,idr;

vector<PT> hpi (vector<L> line) { // salvar (i, j) CCW, (j, i) CW
    rep(i,0,sz(line))line[i].ang = angle(line[i]);
    sort(line.begin(), line.end(), comp);
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(angle(line[i]), angle(pl.back())) != 0) pl.push_back(line[i]);
    idl = N,idr = N;
    dq[idr++]=(0);
    dq[idr++]=(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while (idr - idl > 1 && check(pl[i], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
        while (idr - idl > 1 && check(pl[i], pl[dq[idl]], pl[dq[idl+1]])) idl++;
        dq[idr++]=i;
    }
    while (idr - idl > 1 && check(pl[dq[idl]], pl[dq[idr-1]], pl[dq[idr - 2]])) idr--;
    while (idr - idl > 1 && check(pl[dq[idr-1]], pl[dq[idl]], pl[dq[idl + 1]])) idl++;
    vector<PT> res;
    for (int i = 0; i < idr - idl; ++i){
      int nxt = (idl + i + 1 == idr ? idl : idl + i+1);
      auto IT = lineInter(pl[dq[idl + i]], pl[dq[nxt]]);
      if(IT.ff!=1){
        res.clear();return res;
      }
      res.pb(IT.ss);
    }
    return res;
}

int32_t main(){
  fastio;
  int n;
  cin >> n;
  vector<PT> vec(n);
  rep(i,0,n){
    int x,y;
    cin >> x >> y;
    vec[i] = PT(x,y);
  }
  vector<L> lines;
  reverse(all(vec));

  rep(i,0,n){
    lines.pb(L(vec[i],vec[(i+1)%n]));
  }
  vector<PT> hull = hpi(lines);
  if(sz(hull)==0){
    cout<<"0.0\n";
    return 0;
  }
  double area=polygonArea2(hull);
  area = abs(area)/2.0;
  cout << setprecision(9) << fixed;
  
  cout << area << endl;
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
