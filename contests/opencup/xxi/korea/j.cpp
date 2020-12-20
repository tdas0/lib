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

const int N = 300100;
char s[N];
pii dir(char c){
  if(c=='U')return pii(0,-1);
  if(c=='D')return pii(0,1);
  if(c=='L')return pii(1,0);
  return pii(-1,0);
}
pii acu[N];
int sz[N];
vi comp[N];
int p[N];
pii lazy[N];
int f(int x){
  return p[x]=(p[x]==x?x:f(p[x]));
}
pii operator+(const pii& a,const pii& b){
  return pii(a.ff+b.ff,a.ss + b.ss);
}
pii operator-(const pii& a,const pii& b){
  return pii(a.ff-b.ff,a.ss-b.ss);
}
void join(int a,int b){
  a=f(a);
  b=f(b);
  if(a==b)return;
  if(sz[a] > sz[b])swap(a,b);
  sz[b]+=sz[a];
  p[a]=b;
  for(auto it : comp[a]){
    acu[it] = acu[it] + lazy[a] - lazy[b]; 
    comp[b].pb(it);
  }
  comp[a].clear();
}

int X[N],Y[N];
int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> s[i];
  }
  int q;
  cin >> q;
  map<pii,int> mp;
  for(int i=0;i<q;i++){
    int x,y;
    cin >> x >> y;
    X[i] = x;
    Y[i] = y;
    p[i] = i;
    sz[i]=1;
    acu[i] = lazy[i] = pii(0,0);
    comp[i].pb(i);
    if(mp.count(pii(x,y))){
      join(mp[pii(x,y)],i);
      mp[pii(x,y)] = f(mp[pii(x,y)]);
    }else mp[pii(x,y)] = i;
  }

  int x=0,y=0;
  for(int i=1;i<=n;i++){
    pii d = dir(s[i]);
    x+=d.ff;
    y+=d.ss;
    if(mp.count(pii(x,y))){
      pii cur = pii(x,y);
      int id = mp[pii(x,y)];
      mp.erase(pii(x,y));
      id = f(id);
      lazy[id] = lazy[id] - d;
      cur = cur + d;
      if(mp.count(cur)){
        join(mp[cur],id);
        mp[cur] = f(mp[cur]);
      }else mp[cur] = id;
    }
  }
  rep(i,0,q){
    int id = f(i);
    pii c = lazy[id] + acu[i];
    cout << X[i] - x - c.ff<<" "<< Y[i] -y - c.ss<<endl;
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
