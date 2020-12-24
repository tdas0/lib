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


const int N = 200100;
const int inf = 1e9;
pll pre[N];
ll res[N];
ll s[N],g[N];
ll good(ll val,int id){
  if(pre[id].ff<=val && val<=pre[id].ss)return 1;
  return 0;
}

int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> s[i] >> g[i];
  }
  pre[0] = pii(-inf,inf);

  for(int i=1;i<=n;i++){
    pre[i] = pii(pre[i-1].ff-1,pre[i-1].ss+1);
    pre[i].ff=max(pre[i].ff,s[i]);
    pre[i].ss=min(pre[i].ss,s[i] + g[i]);
    if(pre[i].ff > pre[i].ss){
      cout << -1 << endl;
      return 0;
    }
  }

  res[n] = pre[n].ss;
  for(int i=n-1;i>=1;i--){
    for(int val=1;val>=-1;val--){
      if(good(val + res[i+1],i)){
        res[i] = val + res[i+1];
        break;
      }
    }
  }
  ll tot=0;
  for(int i=1;i<=n;i++){
    tot+=res[i] - s[i];
  }
  cout << tot << endl;
  for(int i=1;i<=n;i++){
    cout << res[i]<<" ";
  }
  cout << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
