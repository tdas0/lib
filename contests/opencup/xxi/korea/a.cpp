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

const int N = 500100;
pii a[N/2];
pii b[N/2];

struct node{
  ll pre,tot;
  node operator+(const node &o) const{  // exemplo de operador de merge
    node r;
    r.tot = tot + o.tot;
    r.pre = min(pre,tot + o.pre);
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, int val){ // pos 0index
    pos+=n;
    st[pos].tot+=val; 
    st[pos].pre = min(0ll,st[pos].tot);
    for(; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    T ra = ini , rb = ini;
    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};

int c[N],A[N];
int rev[N];
int revb[N];

int32_t main(){
  fastio;
  int n,m;
  cin >> n >> m;
  for(int i=1;i<=n;i++){
    cin >> a[i].ff;
    a[i].ss = i;
  }
  sort(a+1,a+1+n,greater<pii>());
  rep(i,1,n+1)A[i] = a[i].ff,rev[a[i].ss] = i;

  for(int i=1;i<=m;i++){
    cin >> b[i].ff;
    b[i].ss = i;
  }
  sort(b+1,b+1+m);
  rep(i,1,m+1)revb[b[i].ss] = i;
  

  ST<node> T(N,{0,0});
  int qtd=m;
  int ptr = 1;
  for(int i=1;i<N;i++){
    while(ptr <=m and b[ptr].ff < i)
      qtd--,ptr++;
    c[i] = qtd;
    T.upd(i,+qtd);
  }
  sort(b+1,b+1+m);

  for(int i=1;i<=n;i++){
    T.upd(i,-A[i]);
  }
  auto get_right = [&](int val){
    int l=1,r = n;
    int ans=-1;
    while(l<=r){
      int mid = (l+r)/2;
      if(A[mid]<val) r = mid - 1;
      else{
        ans = mid;
        l = mid + 1;
      }
    }
    return ans;
  };
  auto get_left = [&](int val){
    int l=1,r=n;
    int ans=-1;
    while(l<=r){
      int mid = (l+r)/2;
      if(A[mid] > val){
        l = mid + 1;
      }else{
        ans = mid;
        r = mid - 1;
      }
    }
    return ans;
  };
  int q;
  cin >> q;
  while(q--){
    int op,id;
    cin >> op >> id;
    if(op == 1 || op==2){
      
      id = rev[id];
      int val = a[id].ff;

      if(op == 1){
        int pos = get_left(val);
        assert(A[pos]==val and (pos==1 || A[pos-1]>val));
        T.upd(pos,+A[pos]);
        a[id].ff++;
        A[pos]++;
        T.upd(pos,-A[pos]);
      }else{
        int pos = get_right(val);
        assert(A[pos]==val and A[pos+1] < val);
        T.upd(pos,+A[pos]);
        a[id].ff--;
        A[pos]--;
        T.upd(pos,-A[pos]);
      }

    }else{
      id = revb[id];
      if(op == 3){
        b[id].ff++;
        T.upd(b[id].ff,+1);
      }else{
        T.upd(b[id].ff,-1);
        b[id].ff--;
      }

    }



    node r = T.query(1,n);
    if(r.pre >= 0)cout << 1<<endl;
    else cout<<0<<endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
