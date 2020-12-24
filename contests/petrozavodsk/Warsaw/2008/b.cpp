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

const int MOD = 1e9- 401;
const int M = MOD-1;

vector<int> P;

vi divi;
void pre(int n){
  int MM = M;
  for(int i=2;i*i<=MM;i++){
    if(MM%i == 0){
      P.pb(i);while(MM%i == 0)MM/=i;
    }
  }
  if(MM>1)P.pb(MM);
  for(int i=1;i*i<=n;i++){
    if(n%i==0){divi.pb(i);
      if(n/i!=i)divi.pb(n/i);
    }
  }

}

vector<ll> fat;
void prefat(int p){
  fat.resize(p);
  fat[0] = 1;
  for(int i=1;i<p;i++)fat[i] = i * fat[i-1]%p;
}

void fatorial(ll n,int p,ll &res,ll &e){
  e=0;
  ll nn = n;
  res = 1;
  while(nn){
    res = 1ll * res * fat[nn%p]%p;
    e+=(nn/p);
    nn/=p;
  }
  if(e&1)res = res * (p-1)%p;
  
  return;

}
ll inverse(ll x,int p){
  return exp(x%p,p-2,p);
}
ll go(int n,int p){
  prefat(p);
  ll tot=0;

  for(int d : divi){
    // n! / (n/d)! / (d!)^(n/d)
    ll A,e1,B,e2,C,e3;
    fatorial(n,p,A,e1);
    fatorial(n/d,p,B,e2);
    fatorial(d,p,C,e3);

    C = exp(C,(n/d),p);
    ll res = A * inverse(C * B %p,p)%p;
    if(e1 - e2 - e3*(n/d) != 0)res = 0;
    tot = (tot + res)%p;

  }
  return tot;
}

ll euclid(ll x, ll y, ll &a, ll &b){
  if(y){
    ll d = euclid(y, x % y, b, a);
    return b -= x / y * a, d;
  }
  return a = 1, b = 0, x;
}
pll crt_coprime(ll a, ll m, ll b, ll n){
  ll x, y; euclid(m, n, x, y);
  ll res = a * (y + m) % m * n + b * (x + n) % n * m;
  if(res >= m * n) res -= m * n;
  return pll(res,m * n);
}

pll crt_coprime(vector<pii>& v){
  if(sz(v) == 1)return v[0];
  pll cur = crt_coprime(v[0].ff,v[0].ss,v[1].ff,v[1].ss);
  
  for(int i=2;i<sz(v);i++){
    cur = crt_coprime(cur.ff,cur.ss,v[i].ff,v[i].ss);
  }
  return cur;
}

ll solve(int n){
  vector<pii> X;
  for(int p : P){
    X.pb(pii(go(n,p),p));
    
  }
  return crt_coprime(X).ff;
}

int32_t main(){
  fastio;
  int n,m;
  cin >> n >> m;
  pre(n);
  m%=MOD;
  cout << exp(m,solve(n),MOD) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
