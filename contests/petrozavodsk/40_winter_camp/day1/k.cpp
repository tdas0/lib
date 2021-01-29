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

const int N = 755;
int d[N][N];
int r[N];
int a[N][N];
int vis[N];


vi g[2*N];
int dist[2*N];
void clear(){
  rep(i,0,2*N)g[i].clear();
  rep(i,0,N){
    vis[i]=0;
  }
}

void solve(){
  int n,k;
  cin >> n >> k;
  clear();
  rep(i,1,n+1)rep(j,1,n+1){
    if(i==j)d[i][j]=0;
    else d[i][j] = 3*N;
  }
  rep(i,1,k+1){
    cin >> r[i];
    rep(j,1,r[i]+1){
      cin >> a[i][j];
    }
    vis[i]=0;
  }
  rep(i,0,n+k+1)g[i].clear();

  int s;
  cin >> s;
  vi ord;
  for(int i=1;i<=s;i++){
    int x;
    cin >> x;
    ord.pb(x);
    vis[x] = 1;
  }
  for(int i=1;i<=k;i++)if(!vis[i]){
    ord.pb(i);
  }
  reverse(all(ord));
  vi res;
  int ptr=0;

  for(int est : ord){
    
    for(int i=1;i<=n+k;i++)dist[i] = -1;
    
    ptr++;
    queue<int> q;
    for(int i=1;i<=r[est];i++){
      q.push(a[est][i]);
      
      dist[a[est][i]] = 0;
      g[a[est][i]].pb(n + ptr);
      g[n + ptr].pb(a[est][i]);
  
    }

    while(!q.empty()){
      int cur = q.front();q.pop();
      for(auto it : g[cur]){
        if(dist[it] == -1){
          dist[it] = dist[cur] + 1;
          q.push(it);
        }
      }
    }

    for(int i=1;i<=n;i++)if(dist[i]==-1)dist[i] = 3*N;

    int ans=0;

    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
        d[i][j] = min(d[i][j],dist[i] + dist[j]);
        if(d[i][j]!=3*N and ans < (d[i][j]/2)){
          ans = (d[i][j]/2);
        }
      }
    }

    res.pb(ans);
  }
  reverse(all(res));
  rep(i,0,s+1)cout << res[i]<<"\n";
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
