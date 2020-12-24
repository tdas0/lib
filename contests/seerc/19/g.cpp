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


const int N = 110;
char mat1[N][N],mat2[N][N];
bool foi[N][N];
struct coisa{
  int a,b,c;
  coisa(){}
  coisa(int A,int B,int C){
    a = A;
    b = B;
    c = C;
  }
  bool operator<(const coisa& o)const{
    return tie(a,b,c) < tie(o.a,o.b,o.c);
  }
};

vi here1[N],here2[N];

int32_t main(){
  fastio;
  int n,m,h;
  cin >> n >> m >> h;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
      cin >> mat1[i][j];
      if(mat1[i][j] == '1'){
        here1[i].pb(j);
      }
    }
  }
  for(int i=0;i<n;i++){
    for(int j=0;j<h;j++){
      cin >> mat2[i][j];
      if(mat2[i][j] == '1'){
        here2[i].pb(j);
      }
    }
  }

  vector<coisa> mn,mx;

  for(int i=0;i<n;i++){
    int a = sz(here1[i]),b = sz(here2[i]);
    if(min(a,b)==0 and max(a,b)>0){
      cout<<-1<<endl;
      return 0;
    }

    for(auto it : here1[i]){
      for(auto it2 : here2[i]){
        mx.pb(coisa(i,it,it2));
      }
    }
    sort(all(here1[i]));
    sort(all(here2[i]));
    
    if(sz(here1[i]) >= sz(here2[i])){
      int dif = sz(here1[i]) - sz(here2[i]);
      for(int j=0;j<dif;j++){
        mn.pb(coisa(i,here1[i][j],here2[i][0]));
      }
      for(int j=dif;j<sz(here1[i]);j++){
        mn.pb(coisa(i,here1[i][j],here2[i][j-dif]));
      }
    }else{
      int dif = sz(here2[i]) - sz(here1[i]);
      for(int j=0;j<dif;j++){
        mn.pb(coisa(i,here1[i][0],here2[i][j]));
      }
      for(int j=dif;j<sz(here2[i]);j++){
        mn.pb(coisa(i,here1[i][j-dif],here2[i][j]));
      }
    }


  }



  cout << sz(mx) << endl;
  sort(all(mx));
  for(auto it : mx){
    cout << it.a<<" "<<it.b<<" "<<it.c<<endl;
  }
  cout << sz(mn) << endl;
  sort(all(mn));
  for(auto it : mn){
    cout << it.a<<" "<<it.b<<" "<<it.c<<endl;
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
