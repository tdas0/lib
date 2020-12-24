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
#define td(v) v.begin(),v.end()
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




const int N = 100100;
const ll inf = 1e18;


struct node{
  ll sum[2];
  ll pot[3];
  //int bad[2];
  int could[2];
  node(){
    rep(i,0,2)sum[i] = could[i] = 0; // bad[i] = 0
    rep(i,0,3)pot[i]=0;
  }
  // bad[0]-> n dirige,bad[1]->n vai na moto
  // pot[0]->potencial pra continuar como carro
  // pot[1]->potencial pra continuar como moto
  // pot[2]->potencial pra virar bebe
  node operator+(const node &o) const{  // exemplo de operador de merge
    node r;
    rep(i,0,3)r.pot[i] = pot[i] + o.pot[i];
    rep(i,0,2){
      r.sum[i] = sum[i] + o.sum[i];
    //  r.bad[i] = bad[i] + o.bad[i];
      r.could[i] = could[i] + o.could[i]; 
    }
    return r;
  }
};
template <class T>
struct ST{
  vector<T> st; int n; 
  T ini; 
  ST(int n , T ini) : st(2*n , ini) , n(n) , ini(ini) {}
  void upd(int pos, T val){ // pos 0index
    for(st[pos += n] = val ; pos /= 2;)
      st[pos] = st[2*pos] + st[2*pos + 1];
  }
  T query(int x , int y){ // [x,y] , x, y -0index
    
    assert(x<n and y<n and x<=y);
    T ra = ini , rb = ini;

    for(x += n, y += n+1 ; x < y ; x/=2 , y/=2){
      if(x&1) ra = ra + st[x] , x++;
      if(y&1) --y , rb = st[y] + rb;
    }
    return ra + rb;
  }
};
ll lc,pc,lm,pm;
ll t,d;
ll a[N];
int32_t main(){
  fastio;
  int n,k;
  cin >> n >> k;
  cin >> lc >> pc >> lm >> pm;
  cin >> t >> d;

  for(int i=0;i<n;i++){
    cin >> a[i];
  }
  sort(a,a+n,greater<int>());


  ST<node> T(n,node());  
  for(int i=0;i<n;i++){
    node cur;
    cur.sum[0] = max(0ll,lc - a[i]);
    cur.sum[1] = max(0ll,lm - a[i]);

    /* 
    cur.bad[0] = (a[i] < lc);
    cur.bad[1] = (a[i] < lm);
    */

    cur.could[0] = (a[i] + d >=lc);
    cur.could[1] = (a[i] + d >=lm);
    cur.pot[0] = max(0ll,min(d,a[i] - lc));
    cur.pot[1] = max(0ll,min(d,a[i] - lm));
    cur.pot[2] = max(0ll,min(d,a[i]-1));

    T.upd(i,cur);
  }
  ll ans = inf;
  for(int x=0;x<=n;x++){
    ll motos = max(1ll*n - 1ll*x*k,0ll);
    
    if(motos == 0){
      node cur = T.query(0,x-1);
      node lixo = (x == n ? node() : T.query(x,n-1));
      if(cur.could[0] < x)continue;
      ll need = cur.sum[0];
      ll give = cur.pot[0] + lixo.pot[2];

      if(need<=give){

        ans = min(ans,need * t + x * pc);
      }

      continue;
    }
    if(x == 0){
      node cur = T.query(0,n-1);
      if(cur.could[1] < n)continue;
      ll need = cur.sum[1];
      ll give = cur.pot[1];
      if(need<=give){
        ans = min(ans,need * t + motos * pm);
      }
      continue;
    }
    node car = T.query(0,x-1);
    node mot = T.query(x,x+motos-1);

    if(car.could[0] < x || mot.could[1] < motos)continue;

    node resto = (x+motos == n ? node() : T.query(x+motos,n-1));

    ll need = 0;
    need =  car.sum[0];
    need+=  mot.sum[1];


    ll give = car.pot[0] + mot.pot[1] + resto.pot[2];

    if(need<=give){
      ans = min(ans,need*t + motos*pm + x*pc);
    }

  }

  if(ans == inf){
    cout << -1 << endl;
    return 0;
  }
  cout << ans << endl;

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
