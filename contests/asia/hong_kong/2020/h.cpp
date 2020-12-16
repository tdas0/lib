// upsolving - naimss
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
inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b,ll e,ll m){
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
      if (e & 1) ans = ans * b % m;
  return ans;
}
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e6 + 10,inf = 1e9 + 7;
int op[N],l[N],r[N],h[N];
int ans[N];
vector<int> Q[N];
int rev[N];

struct node{
  vector<pii> vec;
  void insert(int l,int t){
    while(sz(vec) and vec.back().ss > t)
      vec.pop_back();
    vec.pb(pii(l,t));
  }
  int find(pii info){
    int l = 0,r = sz(vec)-1;
    int ans = -1;
    while(l<=r){
      int mid = (l+r)/2;
      if(vec[mid].ff>=info.ff){
        ans=mid;
        r=mid-1;
      }else l = mid + 1;
    }
    if(ans==-1 || vec[ans].ss >= info.ss)return 0;
    return 1;
  }
};

struct Seg{
  vector<node> tree;
  int n;
  Seg(int nn){
    n = nn;
    tree.resize(4*n + 100);
  }
  void upd(int no,int i,int j,int p,pii v){
    tree[no].insert(v.ff,v.ss);
    if(i==j){
      return;
    }
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    if(p<=mid)upd(l,i,mid,p,v);
    else upd(r,mid+1,j,p,v);
  }
  int query(int no,int i,int j,int L,int R,int H,pii info,int dir){ // info = (>=l,<t);
   // cout << i<<" "<<j<<" "<<L<<" "<<R<<endl;
    if(i > R || j < L)return inf;
    int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
    if(L<=i and j<=R){
      if(!tree[no].find(info))return inf;
    }
    if(i==j)return abs(H - rev[i]);

    if(dir){
        // mais pra direita:

        int op1 = query(r,mid+1,j,L,R,H,info,dir);
        if(op1!=inf)return op1;
        return query(l,i,mid,L,R,H,info,dir);
    }else{
         int op1 = query(l,i,mid,L,R,H,info,dir);
        if(op1!=inf)return op1;
        return query(r,mid+1,j,L,R,H,info,dir);
    }

  }
};

int val[500100];

int32_t main(){
  fastio;
  int t;
  cin >> t;
  
  while(t--){
    int n,m;
    cin >> n >> m;
    vi cmp;
    rep(i,1,n+1)Q[i].clear(),val[i] = -1;
    rep(i,0,m){
      cin >> op[i];
      if(op[i]==0){
        cin>>l[i]>>h[i];
        cmp.pb(h[i]);
        val[l[i]] = i;
      }
      else{
        cin >> l[i] >> r[i] >> h[i];
        Q[r[i]].pb(i);
      }
    }
    Unique(cmp);
    for(int i=1;i<=sz(cmp);i++)rev[i]=cmp[i-1];
    Seg seg(n);
    int T = sz(cmp);

    for(int i=1;i<=n;i++){
      if(val[i]!=-1){
        int H = h[val[i]];
        int p = lower_bound(all(cmp),H)-cmp.begin() + 1;
        seg.upd(1,1,T,p,pii(i,val[i]));
      }
      for(auto id : Q[i]){
        int R = r[id];
        int H = h[id];
        int p = upper_bound(all(cmp),H) - cmp.begin() + 1;
        // [1,p-1] , [p,T]:
        int res = inf;
        if(p<=T || (T==1 and 1<=p and p<=T))res=min(res,seg.query(1,1,T,p,T,H,pii(l[id],id),0));
        if(p-1>=1 || (T==1 and 1<=p-1 and p-1<=T))res=min(res,seg.query(1,1,T,1,p-1,H,pii(l[id],id),1));
        ans[id] = (res==inf ? -1 : res);
      }
    }
    rep(i,0,m)if(op[i]==1)cout<<ans[i]<<endl;

  }



  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
