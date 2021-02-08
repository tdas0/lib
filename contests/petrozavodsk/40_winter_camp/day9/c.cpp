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

const int N = 250100;


struct LAZY{
vector<ll> tree,lazy;
int n;
LAZY(){}
LAZY(int _n){ // pass a vector/array if needed
  n = _n;
  tree.resize(4*n + 100,0);
  lazy.resize(4*n + 100,0);
}

ll f(ll a,ll b){
   return (a>b ? a : b); // max/min (a>b ? a : b)
}
void build(int no,int i,int j){
  lazy[no]=0;
  if(i==j){
    tree[no] = 0;
  }else{
    int m = (i+j)/2;
    int l = 2*no,r=2*no+1;
    build(l,i,m);
    build(r,m+1,j);
    tree[no] = f(tree[l],tree[r]);
  }
}

void propagate(int no,int i,int j){
  if(lazy[no]==0)return;
  tree[no]+=lazy[no];
  if(i!=j){
    lazy[2*no]+=lazy[no];
    lazy[2*no+1]+=lazy[no];
  }
  lazy[no] = 0;
}

  void update(int no,int i,int j,int a,int b,ll v){
    propagate(no,i,j);
    if(i>b || j<a || i>j)return;
    if(a<=i && j<=b){
      tree[no] += v;
      if(i!=j){
        lazy[2*no]+=v;
        lazy[2*no+1]+=v;
      }
      return;
    }
    int m = (i+j)/2;
    int l = 2*no,r=2*no+1;
    update(l,i,m,a,b,v);
    update(r,m+1,j,a,b,v);  
    tree[no] = f(tree[l],tree[r]);
  }

  ll query(int no,int i,int j,int a,int b){
    if(i>b || j<a || i>j)return 1e15;
    
    propagate(no,i,j);
    
    if(a<=i && j<=b)return tree[no];
    
    int m = (i+j)/2;
    int l = 2*no,r=2*no+1;
    
    return f(query(l,i,m,a,b),query(r,m+1,j,a,b));
  }

};

int n,k;
multiset<int> S[N];
int x[N],y[N],c[N];
const int inf = 1e9;
int ok(int R){
  LAZY L(N);

  rep(i,1,k+1){
    S[i].clear();
    S[i] = {-inf,inf};
  }


  vector<int> ids;
  rep(i,1,n+1){
    ids.pb(i);
  }
  sort(all(ids),[&](int a,int b){
    return x[a] < x[b];
  });

  int ptr=0;

  auto update = [&](int id,int v){
    int cor = c[id];
    if(v==-1)S[cor].erase(S[cor].find(y[id]));

    int prv = *prev(S[cor].upper_bound(y[id]));
    int nxt = *S[cor].upper_bound(y[id]);
    int l = max({y[id] - R,prv+1,1});
    int r = min(y[id],nxt-R-1);
    if(v == 1)S[cor].insert(y[id]);
    if(l<=r)L.update(1,1,N,l,r,v);
  };

  for(auto it : ids){
    while(ptr < n and x[it] - x[ids[ptr]] > R){
      update(ids[ptr],-1);
      ptr++;
    }
    update(it,1);
    if(L.query(1,1,N,1,N) == k){
      return 1;
    }
  }
  return 0;
}

int32_t main(){
  fastio;
  cin >> n >> k;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i] >> c[i];
  }
  int l = 0,r = N;
  int ans = N;
  
  while(l<=r){
    int m = (l+r)/2;
    if(ok(m)){
      ans = m,r=m-1;
    }else l = m +1;
  }
  cout << ans << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
