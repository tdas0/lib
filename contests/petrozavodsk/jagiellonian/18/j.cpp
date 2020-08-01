// upsolving
// hashing with log + modulos
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

const int N = 1500100;
ld Log[N],pre[N];

const ld EPS = 1e-2;
const int M = 1e9 + 7;

int fat[N];
int inv[N];

bool check(int i,int j,ld X,int mul,ld fi){
  if(abs(fi - X) > EPS)return 0;
  int x = 1ll*fat[i]*inv[j]%M*inv[i-j]%M;
  if(x == mul)return 1;
  return 0;
}

void solve(){
  int t,m;
  cin >> t >> m;
  ld X = 0;
  int mul = 1;
  for(int i=1;i<=t;i++){
    int x;
    cin>>x;
    mul = 1ll*mul*x%M;
    X += Log[x];
  }
  
  for(int k = 0; k<= m; k ++ ){
    int l = 1,r = m-k;
    while(l<=r){
    // test for C(k + mid,k)
      int mid = (l+r)/2;
      ld fi = pre[k + mid] - pre[k] - pre[mid];
      if(check(k + mid,k,X,mul,fi)){
        cout<<"YES"<<endl;
        cout << k + mid <<" "<<k << endl;
        return;
      }
      if(fi < X){
        l = mid + 1;
      }else r = mid - 1;
    }
  }

  cout <<"NO" << endl;

}

int32_t main(){
  fastio;

  fat[0] = 1;
  for(int i=1;i<N;i++){
    Log[i] = log2(i);
    fat[i] = (1ll*i*fat[i-1])%M;
  }
  inv[N-1] = exp(fat[N-1],M-2,M);
  for(int i=N-2;i>=0;i--){
    inv[i] = 1ll*inv[i+1]*(i+1)%M;
  }

  for(int i=1;i<N;i++){
    pre[i] = pre[i-1] + Log[i];
  }
 
  int q;
  cin >> q;
  while(q--){
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
