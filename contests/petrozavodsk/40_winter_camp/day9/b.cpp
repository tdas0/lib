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

const int N = 300100;
int pai[N],mn[N],sz[N];


int A[N],B[N],C[N];
int f(int x){
  return pai[x] = (pai[x]==x?x:f(pai[x]));
}

void join(int a,int b){
  a=f(a),b=f(b);
  assert(a!=b);
  if(sz[a] > sz[b])swap(a,b);
  pai[a] = b;
  sz[b]+=sz[a];
  mn[b] = min(mn[b],mn[a]);
}

vi ev[N];


int32_t main(){
  fastio;
  int n,k;
  cin >> n >> k;
  vector<int> v;
  rep(i,1,n)cin >> A[i] >> B[i] >> C[i],v.pb(i);
  sort(all(v),[&](int a,int b){
    return C[a] < C[b];
  });
  rep(i,1,n+1){
    pai[i] = i,sz[i]=1,mn[i] = i;
  }
  for(int id : v){
    int i1 = mn[f(A[id])];
    int i2 = mn[f(B[id])];
    join(A[id],B[id]);
    ev[max(i1,i2)].pb(C[id]);
  }
  multiset<int> S;
  ll sum=0;
  for(int i=1;i<=n;i++){
    for(auto it : ev[i])S.insert(it),sum+=it;

    while(sz(S) > k){
      int val = *S.begin();
      S.erase(S.find(val));
      sum-=val;
    }
    cout << sum << endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
