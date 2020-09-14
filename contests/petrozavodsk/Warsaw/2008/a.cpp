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
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
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


const int N = 200100;
int v[N],b[N];


struct LAZY{
vector<ll> mn,lazy,mx;
int n;
LAZY(){}
LAZY(int _n){ // pass a vector/array if needed
  n = _n;
  mn.resize(4*n + 100,0);
  lazy.resize(4*n + 100,0);
  mx.resize(4 * n + 100,0);
}

void propagate(int no,int i,int j){
  if(lazy[no]==0)return;
  mn[no]+=lazy[no];
  mx[no]+=lazy[no];
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
    lazy[no]+=v;
    propagate(no,i,j);
    return;
  }
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  update(l,i,m,a,b,v);
  update(r,m+1,j,a,b,v);  
  mn[no] = min(mn[l],mn[r]);
  mx[no] = max(mx[l],mx[r]);
}
void upd(int a,int b,ll v){
  update(1,1,n,a,b,v);
}

ll query(int no,int i,int j,int a,int b){
  if(i>b || j<a || i>j)return 1e15;
  
  propagate(no,i,j);
  
  if(a<=i && j<=b)return mn[no];
  
  int m = (i+j)/2;
  int l = 2*no,r=2*no+1;
  
  return min(query(l,i,m,a,b),query(r,m+1,j,a,b));
}
ll query(int a,int b){
  return query(1,1,n,a,b);
}

void pushdown(int no,int i,int j){
  propagate(no,i,j);
  int m = (i+j)/2,l=2*no,r=2*no+1;
  if(i!=j){
    propagate(l,i,m);
    propagate(r,m+1,j);
    mn[no] = min(mn[l],mn[r]);
    mx[no] = max(mx[l],mx[r]);
  }
 } 

  int bbL(int no,int i,int j,int L,int R,int val){
    pushdown(no,i,j);
    if(i > R or j<L)return N;// bad...
    if(mx[no] <= val)return N;
    if(i == j)return i;
    int m = (i+j)/2;
    int l=2*no,r=2*no + 1;

    if(i<L or j>R){
      return min(bbL(l,i,m,L,R,val),bbL(r,m+1,j,L,R,val));
    }
    if(mx[l] > val){
      return bbL(l,i,m,L,R,val);
    }
    return bbL(r,m+1,j,L,R,val);
  }
  int bbL(int L,int R,int val){
    return bbL(1,1,n,L,R,val);
  }
  int bbR(int no,int i,int j,int L,int R,int val){
    pushdown(no,i,j);
    if(i > R or j<L)return 0;// bad...
    if(mn[no] > val)return 0;
    if(i == j)return i;
    int m = (i+j)/2;
    int l=2*no,r=2*no + 1;

    if(i<L or j>R){
      return max(bbR(l,i,m,L,R,val),bbR(r,m+1,j,L,R,val));
    }

    if(mn[r] <= val){
      return bbR(r,m+1,j,L,R,val);
    }
    return bbR(l,i,m,L,R,val);
  }
  int bbR(int L,int R,int val){
    return bbR(1,1,n,L,R,val);
  }
};


int32_t main(){
  fastio;
  int m,n;
  cin >> m >> n;//inverti
  for(int i=1;i<=m;i++){
    cin >> b[i];
  }
  sort(b + 1, b + 1 + m);
  for(int i=1;i<=n;i++)cin >> v[i];
  sort(v + 1 , v + 1 + n,greater<int>());
  LAZY L(m);
  for(int i=1;i<=m;i++)
    L.upd(i,i,b[i]);

  bool ok = 1;
  for(int i=1;i<=n;i++){
    if(v[i] > m){
      ok=0;break;
    }
    if(L.query(m - v[i] + 1,m) <= 0){
      ok = 0;break;
    }
    L.upd(m - v[i] + 1,m,-1);
    if(v[i] == m)continue;
    // reorder
    int small = L.query(m - v[i] + 1,m);
    int posR = L.bbR(m- v[i] + 1,m,small);
    assert(posR > 0);
    int cnt = (posR - (m-v[i]+1) + 1);
    int posL = L.bbL(1,m - v[i],small);
    
    int offer = (m - v[i] - posL + 1);
    int put = min(offer,cnt);
    
    if(put <= 0)continue;
    L.upd(posR - put + 1,posR,+1);
    L.upd(posL,posL + put - 1,-1);
  }
  cout << (ok ? "YES" : "NO" ) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
