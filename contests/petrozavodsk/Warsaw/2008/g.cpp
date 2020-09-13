#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb(x) push_back(x)
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
#define sz(v) (int)v.size()
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll a,ll b,ll m){
    if(b==0LL) return 1LL;
    if(b==1LL) return mod(a,m);
    ll k = mod(exp(a,b/2,m),m);
    if(b&1LL){
        return mod(a*mod(k*k,m),m);
    }
    else return mod(k*k,m);
}
const int M = 1e9 + 9;
template<class T>
struct Mat{
  int n, m; vector< vector<T> > d;
  Mat(int n , int m): n(n) , m(m){
    d.assign(n , vector<T>(m));
  }
  Mat() : Mat(0,0) {}
  
  Mat  operator*(const Mat&a){ // m == a.n
    Mat x(n,a.m);
    rep(i,0,n) rep(j,0,m) rep(k,0,a.m)
      x.d[i][k] = (1ll * x.d[i][k] + 1ll * d[i][j] * a.d[j][k])%M;
    return x;
  }
  Mat operator+(const Mat&a){
    return Mat(*this)+= a;
  }
  Mat operator-(const Mat&a){
    return Mat(*this)-= a;
  }
  Mat & operator*=(const Mat&a){
    return *this = (*this)*a;
  }
  Mat & operator^=(const ll& x){
    return *this = pow(*this , x);
  }
  Mat operator^(const ll &x){
    return Mat(*this)^= x;
  }
  friend Mat pow(Mat a, ll p){
    Mat res(a.n,a.m); rep(i,0,a.n) res.d[i][i] = 1;
    for(; p ; p/=2 , a *= a) if(p&1) res *= a;
    return res;
  }
 };


const int N = 21;
int ok[N][N]; 
int bad[N];
int32_t main(){
  fastio;
  int n,m,k,d;
  cin >> n >> m >> k >> d;
  ll res = 0;
  for(int i=0;i<m;i++){
    int a,b;
    cin >> a >> b;
    a--;b--;
    ok[a][b] = ok[b][a] = 1;
  }
  if(d == 1){
    cout << (k==1) << endl;
    return 0;
  }
  for(int i=0;i<n;i++)bad[i] = 0;
  for(int msk=0;msk<(1<<k);msk++){
    Mat<ll> mat(n,n);
    int cnt=0;
    rep(j,0,k)if(msk&(1<<j)){
      bad[j] = 1;
      cnt++;
    }else bad[j] = 0;

    rep(i,0,n){
      rep(j,0,n){
        if(ok[i][j] and !bad[i] and !bad[j]){
          mat.d[i][j] = 1;
        }else mat.d[i][j] = 0;
      }
    }
    mat^=(d-1);
    ll tot=0;
    rep(i,0,n)rep(j,0,n){
      tot=(tot + mat.d[i][j])%M;
    }
    if(cnt&1)res = (res + M - tot)%M;
    else res = (res + tot)%M;
  }
  
  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
