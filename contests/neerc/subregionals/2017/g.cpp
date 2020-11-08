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

vi g[N],und[N];
int vis[N];
vi vec;
int t[N],a[N],b[N];
void dfs(int v){
  vis[v]=1;
  vec.pb(v);
  for(int to : g[v])if(!vis[to]){
    dfs(to);
  }
}

int n,m,s;
char mnR[N];
pii dire[N];

void dfs2(int v){
  vis[v] = 1;
  vec.pb(v);
  for(int to : g[v])if(!vis[to]){
    dfs2(to);
  }
  for(int id : und[v]){
    int to = (a[id]+b[id]-v);
    if(!vis[to]){
      dire[id] = pii(v,to);
      dfs2(to);
    }
  }
}

int32_t main(){
  fastio;
  cin >> n >> m >> s;
  for(int i=0;i<m;i++){
    cin >> t[i] >> a[i] >> b[i];
    if(t[i]==1){
      g[a[i]].pb(b[i]);
    }else{
      und[a[i]].pb(i);
      und[b[i]].pb(i);
    }
  }
  dfs(s);
  // MINIMO:
  int resmn = sz(vec);
  for(int i=0;i<m;i++){
    if(t[i]==2){
      if(vis[a[i]])mnR[i] = '-';
      else mnR[i] = '+';
    }
  }
  // MAXIMO:
  for(int i=1;i<=n;i++)vis[i]=0;
  vec.clear();
  dfs2(s);
  int resmx = sz(vec);
  cout << resmx<<endl;
  for(int i=0;i<m;i++){
    if(t[i]==2){
      if(dire[i] == pii(a[i],b[i]))cout<<"+";
      else cout<<"-"; 
    }
  }
  cout<<endl;
  cout<<resmn<<endl;
  for(int i=0;i<m;i++){
    if(t[i]==2){
      cout<<mnR[i];
    }
  }
  cout<<endl;


  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
