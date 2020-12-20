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

 typedef struct snode* sn;
struct snode { //////// VARIABLES
  sn p, c[2]; // parent, children
  sn extra; // extra cycle node for "The Applicant"
  bool flip = 0; // subtree flipped or not
  int val,sz; // value in node, # nodes in current splay tree
  int sub, vsub = 0; // vsub stores sum of virtual children
  ll sum = 0;
  snode(ll _val) : val(_val) {
    sum = _val;
    p = c[0] = c[1] = extra = NULL; calc(); }
  friend int getSz(sn x) { return x?x->sz:0; }
  friend int getSub(sn x) { return x?x->sub:0; }
  friend ll getSum(sn x){return x?x->sum:0;}
  void prop() { // lazy prop
    if (!flip) return;
    swap(c[0],c[1]); flip = 0;
    rep(i,0,2) if (c[i]) c[i]->flip ^= 1;
  }
  void calc() { // recalc vals
    rep(i,0,2) if (c[i]) c[i]->prop();
    sz = 1+getSz(c[0])+getSz(c[1]);
    sub = 1+getSub(c[0])+getSub(c[1])+vsub;
    sum = val + getSum(c[0])+getSum(c[1]);
  }
  //////// SPLAY TREE OPERATIONS
  int dir() {
    if (!p) return -2;
    rep(i,0,2) if (p->c[i] == this) return i;
    return -1; // p is path-parent pointer
  } // -> not in current splay tree
  // test if root of current splay tree
  bool isRoot() { return dir() < 0; } 
  friend void setLink(sn x, sn y, int d) {
    if (y) y->p = x;
    if (d >= 0) x->c[d] = y; }
  void rot() { // assume p and p->p propagated
    assert(!isRoot()); int x = dir(); sn pa = p;
    setLink(pa->p, this, pa->dir());
    setLink(pa, c[x^1], x); setLink(this, pa, x^1);
    pa->calc(); calc();
  }
  void splay() {
    while (!isRoot() && !p->isRoot()) {
      p->p->prop(), p->prop(), prop();
      dir() == p->dir() ? p->rot() : rot();
      rot();
    }
    if (!isRoot()) p->prop(), prop(), rot();
    prop();
  }
  sn fbo(int b) { // find by order
    prop(); int z = getSz(c[0]); // of splay tree
    if (b == z) { splay(); return this; }
    return b < z ? c[0]->fbo(b) : c[1] -> fbo(b-z-1);
  }
  //////// BASE OPERATIONS
  void access() { // bring this to top of tree, propagate
    for (sn v = this, pre = NULL; v; v = v->p) {
      v->splay(); // now switch virtual children
      if (pre) v->vsub -= pre->sub;
      if (v->c[1]) v->vsub += v->c[1]->sub;
      v->c[1] = pre; v->calc(); pre = v;
    }
    splay(); assert(!c[1]); // right subtree is empty
  }
  void makeRoot() { 
    access(); flip ^= 1; access(); assert(!c[0] && !c[1]); }
  //////// QUERIES
  friend sn lca(sn x, sn y) {
    if (x == y) return x;
    x->access(), y->access(); if (!x->p) return NULL;
    x->splay(); return x->p?:x; // y was below x in latter case
  } // access at y did not affect x -> not connected
  friend bool connected(sn x, sn y) { return lca(x,y); } 
  // # nodes above
  int distRoot() { access(); return getSz(c[0]); } 
  sn getRoot() { // get root of LCT component
    access(); sn a = this; 
    while (a->c[0]) a = a->c[0], a->prop();
    a->access(); return a;
  }
  sn getPar(int b) { // get b-th parent on path to root
    access(); b = getSz(c[0])-b; assert(b >= 0);
    return fbo(b);
  } // can also get min, max on path to root, etc
  //////// MODIFICATIONS
  void set(int v) { access(); val = v; calc(); } 
  friend void link(sn x, sn y, bool force = 0) { 
    assert(!connected(x,y)); 
    if (force) y->makeRoot(); // make x par of y
    else { y->access(); assert(!y->c[0]); }
    x->access(); setLink(y,x,0); y->calc();
  }
  friend void cut(sn y) { // cut y from its parent
    y->access(); assert(y->c[0]);
    y->c[0]->p = NULL; y->c[0] = NULL; y->calc(); }
  friend void cut(sn x, sn y) { // if x, y adj in tree
    x->makeRoot(); y->access(); 
    assert(y->c[0] == x && !x->c[0] && !x->c[1]); cut(y); }
};
const int N = 250500;
sn LCT[N];
vi g[N];
int deg[N];
int ptr[N];

bool can_add(int i,int j){
  while(ptr[j] < sz(g[j]) and g[j][ptr[j]] < i)
    ptr[j]++;
  int a=0;
  int p = ptr[j];
  while(p < sz(g[j])){
    if(g[j][p] > j)break;
    a++;
    if(a > 2)return false;     
    if(deg[g[j][p]]==2)return false;
    p++;
  }
  return true;
}

bool can_add2(int i,int j){
   while(ptr[j] < sz(g[j]) and g[j][ptr[j]] < i)
    ptr[j]++;
  int a=0;
  int p = ptr[j];
  
  while(p < sz(g[j])){
    if(g[j][p] > j)break;
    a++;
    if(a > 2)return false;     
    if(a==2){
      if(LCT[g[j][p]]->getRoot()==LCT[g[j][p-1]]->getRoot())return false;
    }
    p++;
  }
  return true;
}

void add(int i,int j){
  for(auto to : g[j]){
    if(i<=to and to<=j){
      deg[to]++;
      deg[j]++;
      link(LCT[to],LCT[j],1);
    }
  }
}
void remove(int i,int j){
  for(auto to : g[i]){
    if(i<=to and to<=j){
      deg[to]--;
      deg[i]--;
      cut(LCT[i],LCT[to]);
    }
  }
}


int cnt[4*N];
int lazy[4*N];
int mn[4*N];
void flush(int no,int i,int j){
  if(!lazy[no])return;
  int l=no<<1,r=no<<1|1;
  mn[no]+=lazy[no];
  if(i!=j){
    lazy[l]+=lazy[no];
    lazy[r]+=lazy[no];
  }
  lazy[no]=0;
}
void upd(int no,int i,int j,int a,int b,int v){
  flush(no,i,j);
  if(i>b || j < a)return;
  if(a<=i and j<=b){
    lazy[no]+=v;
    flush(no,i,j);
    return;
  }
  int l=no<<1,r=no<<1|1,mid = (i+j)>>1;
  upd(l,i,mid,a,b,v);
  upd(r,mid+1,j,a,b,v);
  mn[no]=min(mn[l],mn[r]);
  cnt[no]=0;
  if(mn[l]==mn[no])cnt[no]+=cnt[l];
  if(mn[r]==mn[no])cnt[no]+=cnt[r];
}
void build(int no,int i,int j){
  if(i==j){
    mn[no]=0;
    cnt[no]=1;
    return;
  }
  int l=no<<1,r=no<<1|1,mid = (i+j)>>1;
  build(l,i,mid);
  build(r,mid+1,j);
  cnt[no]=j-i+1;
  mn[no]=0;

}
pii query(int no,int i,int j,int a,int b){
  flush(no,i,j);
  if(i > b || j < a)return pii(1000000,0);
  if(a<=i and j<=b)return pii(mn[no],cnt[no]);
  int l=no<<1,r=no<<1|1,mid = (i+j)>>1;
  pii A = query(l,i,mid,a,b);
  pii B = query(r,mid+1,j,a,b);
  pii C=pii(0,0);
  C.ff=min(A.ff,B.ff);
  if(A.ff==C.ff)C.ss+=A.ss;
  if(B.ff==C.ff)C.ss+=B.ss;
  return C;
}
typedef array<int,3> arr;
vector<arr> rem[N];
int32_t main(){
  fastio;
  int n,m;
  cin>>n>>m;
  build(1,1,n);
  for(int i=0;i<m;i++){
    int a,b;
    cin >> a >> b;
    g[a].pb(b);
    g[b].pb(a);
    if(a > b)swap(a,b);
    rem[a+1].pb({b,n,+1});
    upd(1,1,n,b,n,-1);
  }
  rep(i,1,n+1)LCT[i] = new snode(i),sort(all(g[i]));
  rep(i,1,n+1){
    upd(1,1,n,i,n,+1);
  }
  int j = 1;
  ll res=0;
  for(int i=1;i<=n;i++){
    for(auto it : rem[i]){
      upd(1,1,n,it[0],it[1],it[2]);
    }
    if(i>=1)upd(1,1,n,i,n,-1);
    while(j<=i)j++;
    while(j<=n and can_add(i,j) and can_add2(i,j)){
      add(i,j);
      j++;
    }
    remove(i,j-1);
    pii q = query(1,1,n,i,j-1);
    if(i<j)
      res+=q.ss;
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
