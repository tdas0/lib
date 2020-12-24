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
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b, ll e ,ll m) {
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return mod(ans,m);
}

const int N = 300100;
int v[N];
int dp[N];
int n,k;

struct node{
  int x;
  node operator+(const node &rhs) const{  // exemplo de operador de merge
    node r;
    r.x = x|rhs.x;
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, T val){ // pos 0index
    for(st[pos += n] = val ; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};


bool ok(int x){
  for(int i=1;i<=n;i++){
    dp[i]=0;
  }
  // dp[i] = 1 se pode terminar em i:
  int j = 1;
  int some = 0;
  dp[0] = 1;
  ST<node> T(n+1,{0});
  T.upd(0,{1});
  for(int i=1;i<=n;i++){
    while(v[i] - v[j] > x)j++;
    int L = j-1,R = i-k;
    if(L<=R and T.query(L,R).x){
      T.upd(i,{1});
    }
  }
  int res = T.query(n,n).x;
  return res;
}

int32_t main(){
  fastio;
  cin>>n>>k;
  for(int i=1;i<=n;i++){
    cin >> v[i];
  }
  sort(v+1,v+1+n);
  int l = 0,r = 1e9 + 7;
  int ans = r;
  while(l<=r){
    int mid = (l+r)/2;
    if(ok(mid)){
      ans = mid;
      r = mid - 1;
    }else l = mid + 1;
  }
  cout << ans << endl;
  
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
