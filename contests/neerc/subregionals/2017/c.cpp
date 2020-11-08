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
#define int long long
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


const int N = 5;
ll a[N],p[N],t[N];
int cela(int a,int b){
  return (a+b-1)/b;
}
int32_t main(){
  fastio;
  int f,T;
  cin >> f >> T;
  cin >> t[0];
  a[0] = 1,p[0] = 0;
  for(int i=1;i<=2;i++){
    cin >> a[i] >> t[i] >> p[i];
    if(t[i]>=t[0]){
      a[i]=a[0];
      p[i]=p[0];
      t[i]=t[0];
    }
  }
  ll res = LLONG_MAX;
  rep(iter,0,2){

    for(ll K1= 0;K1*a[1]<=f;K1++){
      if(K1 * t[1] > T)break;
      ll need = f - a[1] * K1;
      ll K2 = cela(need,a[2]);
      ll H = K1 * t[1] * a[1] + t[2] * need;

      if(H > T)continue;
      ll x = 0;
      if(t[0]!=t[2]){
        x = min(need,(T - H)/(t[0] - t[2]));// numero de t0s a comprar:
      }
      ll buy2 = cela(need - x,a[2]);
      ll cost = K1 * p[1] + buy2 * p[2];
      
      res = min(res,cost);
    }
    //
    swap(a[1],a[2]);
    swap(p[1],p[2]);
    swap(t[1],t[2]);
  }
  if(res == LLONG_MAX){
    cout << -1 << endl;
  }else cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
