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
const int N = 100100;
ll t[N];
ll cela(ll a,ll b){
  return (a+b-1)/b;
}
int32_t main(){
  fastio;
  ll n,m,a,d;
  cin>>n>>m>>a>>d;
  for(int i=1;i<=m;i++){
    cin >> t[i];
  }
  t[m+1] = n * a;
  int j = 1;
  ll curt = 0;
  ll res = 0;
  ll jump = (d/a) + 1;
  assert(jump * a > d);
  assert((jump-1)*a <= d);
  while(true){
    
    while(j<=m and t[j] <= curt)j++;
    
    ll nxta = cela(curt,a) * a;
    
    if(curt%a == 0)nxta+=a;
    
    if(j>m and nxta > n*a)break;
    
    if(curt > n*a)nxta = 2e18;

    //cout <<"GO: ";
    if(curt < n * a and nxta < t[j]){
      // quanto posso pular de vez?
      ll pulos = max((t[j] - nxta - d)/(a * jump),0LL) + 1;
      ll pulos2 = max((n*a - nxta - d)/(a*jump),0LL) + 1;
      pulos = min(pulos,pulos2);
      res+=pulos;
      curt = nxta + a*jump*(pulos-1) + d;
     // cout <<"PULOS "<<pulos<<" "<<nxta<<" "<<jump*a*pulos<<" "<<curt<<endl;
    }else{
      res++;
      curt = t[j] + d;
    }
  }

  cout << res << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
