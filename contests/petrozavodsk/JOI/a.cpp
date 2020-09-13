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
#define prl cerr<<"called: "<< __LINE__<<endl;
typedef long long ll;
typedef pair<int,int> pii;
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


#define lb(v,x) lower_bound(all(v),x)
int res=0;
void calc(vi& up,int mid,vi& down){
  if(sz(up) < sz(down)){
      // junta por aqui:
      for(int i = 0;i < sz(up);i++){
        // pega i+1 caras:
        if(up[i] < mid){
          // posso juntar:
          int pos = lower_bound(all(down),mid,greater<int>()) - down.begin() - 1;
          res=max(res,1 + i + pos);
        }
        int pos = lower_bound(all(down),up[i],greater<int>()) - down.begin() - 1;
        res = max(res,i + pos);
      }
  }else{
    for(int i = 0;i<sz(down);i++){
      if(down[i] > mid){
        int pos = (lb(up,mid) - up.begin()) - 1;
        res = max(res,1 + i + pos);
      }
      int pos = (lb(up,down[i]) - up.begin()) - 1;
      res = max(res,i + pos);
    }
  }
}
void Merge(vi &a,vi& b,bool f){
  if(sz(a) < sz(b))swap(a,b);
  rep(i,0,sz(b)){
    if(f)a[i] = min(a[i],b[i]);
    else a[i] = max(a[i],b[i]);
  }
}

const int N = 100100;
vi g[N];
vi order;
int pai[N];
int H[N];
vi Up[N],Down[N];
void dfs(int v,int p = -1){
  for(int to : g[v])if(to!=p){
    pai[to] = v;
    dfs(to,v);
  }
  order.pb(v);
}
const int inf = 1e9 + 7;



int32_t main(){
  fastio;
  int n;
  cin>>n;
  for(int i=1;i<=n;i++){
    cin >> H[i];
  }
  for(int i=1;i<n;i++){
    int a,b;
    cin>>a>>b;
    g[a].pb(b);
    g[b].pb(a);
  }
  dfs(1);

  for(int i : order){
    
    Up[i].pb(0);
    Down[i].pb(inf);

    for(int to : g[i])if(to!=pai[i]){
      calc(Up[i],H[i],Down[to]);
      calc(Up[to],H[i],Down[i]);
      Merge(Up[i],Up[to],1);
      Merge(Down[i],Down[to],0);
    }

    if(lb(Up[i],H[i]) == Up[i].end())Up[i].pb(H[i]);
    else *lb(Up[i],H[i]) = H[i];
    
    if(lower_bound(all(Down[i]),H[i],greater<int>()) == Down[i].end())Down[i].pb(H[i]);
    else *lower_bound(all(Down[i]),H[i],greater<int>()) = H[i];

    res = max(res,max(sz(Up[i]),sz(Down[i])) - 1);
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
