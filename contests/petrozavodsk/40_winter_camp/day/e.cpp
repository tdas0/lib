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

int C;
double V;

const double PI = acos(-1);
const double EPS = 1e-3;
const double PI2 = PI/2.0;

void go(double x,double y,double&L,double&R){
  double l = (-x - sqrt(x*x+2*10*x*x/V/V*(-10*x*x/2.0/V/V - y)))/(-10*x*x/V/V);
  double r = (-x + sqrt(x*x+2*10*x*x/V/V*(-10*x*x/2.0/V/V - y)))/(-10*x*x/V/V);
  if(l > r)swap(l,r);
  L = max(L,l);
  R = min(R,r);
}

void solve(){
  cin >> C;
  V = C;
  int n;
  cin >> n;
  double L = 0,R = 1e18;
  int ok = 1;
  for(int i=0;i<n;i++){
    int x,y;
    cin >> x >> y;
    go(x,y,L,R);
  }
  cout << setprecision(3)<<fixed;
  cout << L + EPS << endl;
  
}

int32_t main(){
  fastio;
  int t;
  cin >> t;
  while(t--){
    solve();
  }

  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
