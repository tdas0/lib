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


struct event{
  int x,yd,yp,t;
  event(){}
  event(int x,int yd,int yp,int t):x(x),yd(yd),yp(yp),t(t){}
};
const int N = 200100;
int tree[4*N];
int tam[4*N];
int lazy[4*N];

int A[N],B[N],C[N],D[N];
vi cy;
void build(int no,int i,int j){

    tree[no] = lazy[no]= 0;
  if(i == j){
    tam[no] = cy[i + 1] - cy[i]; 
    return;
  }
  int mid = (i+j)>>1,l = no << 1 ,r = no << 1 | 1;
  build(l,i,mid);
  build(r,mid+1,j);
  tam[no] = tam[l] + tam[r];
}

void flush(int no,int i,int j){
  if(lazy[no] == 0)return;
  
  tree[no] = tam[no] - tree[no];

  int l = no << 1 ,r = no << 1 | 1;
  if(i!=j){
    lazy[l]^=1;
    lazy[r]^=1;
  }
  lazy[no] = 0;
}
void upd(int no,int i,int j,int a,int b){
  flush(no,i,j);
  if(i > j || i > b || j < a)return;
  if(a<=i and j<=b){
    lazy[no]^=1;
    flush(no,i,j);
    return;
  }
  int mid = (i+j)>>1,l=no<<1,r=no<<1|1;
  upd(l,i,mid,a,b);
  upd(r,mid+1,j,a,b);
  tree[no] = tree[l] + tree[r];
}

ll query(int no,int i,int j,int a,int b){
  flush(no,i,j);
  if(i>j || i > b || j < a)return 0;
  if(a<=i and j<=b)return tree[no];
  int mid = (i + j) >> 1 , l = no << 1 ,r = no << 1 | 1;
  return query(l,i,mid,a,b) + query(r,mid+1,j,a,b);
}

int32_t main(){
  fastio;
  int m,n,k;
  cin >> m >> n >> k;
  
  for(int i=0;i<k;i++){
    cin >> A[i] >> B[i] >> C[i] >> D[i];
    B[i]++;D[i]++;
    cy.pb(C[i]);

    cy.pb(D[i]);
  } 
  Unique(cy);

  build(1,0,sz(cy)-2);
  vector<event> ev;
  for(int i=0;i<k;i++){
    int l = lower_bound(all(cy),C[i]) - cy.begin();
    int r = lower_bound(all(cy),D[i]) - cy.begin() - 1;
    ev.pb(event(A[i],l,r,1));
    ev.pb(event(B[i],l,r,-1));
   // cout << "["<<l<<","<<r<<"]\n";
  }
  ll res=0;
  sort(all(ev),[&](event a,event b){
    if(a.x != b.x)return a.x < b.x;
    return a.t < b.t;
  });

  int tam = sz(cy) - 2;
  upd(1,0,tam,ev[0].yd,ev[0].yp);

  //return 0;
  for(int i=1;i < sz(ev);i++){
    query(1,0,tam,0,tam);
   // cout <<"["<< ev[i-1].x<<" "<<ev[i].x<<"] == "<<tree[1]<<endl;
    res+=1ll * query(1,0,tam,0,tam) * (1ll*ev[i].x - 1ll*ev[i-1].x);
    //cout << "att "<<ev[i].yd<<" "<<ev[i].yp<<" "<<query(1,0,tam,ev);
   // cout << "update "<<ev[i].yd<<" "<<ev[i].yp << endl;
    upd(1,0,tam,ev[i].yd,ev[i].yp);

  }

  res = 1LL*n*m - res;
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
