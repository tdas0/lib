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

const int N = 5050;
int a[N];
int b[N];

int vec[N];

int go(vi v){

  int ptr=0;
  int res=0;
  for(int x : v){
    vec[ptr++] = x;
    while(ptr>=3){
      int cnt=3;
      if(vec[ptr-1]==3 and vec[ptr-2]==3 and vec[ptr-3]==3){
        cnt = 0;
      }else{
        if(vec[ptr-1]==3 and vec[ptr-2]==1 and vec[ptr-3]==3){
          cnt=1;
        }else cnt=3;
      }
      if(cnt >= 2)break; // 11,111

      if(cnt == 0){
        res+=2; // 333 -> 3
      }
      ptr-=3;
      vec[ptr++]=3; //
    }
  }
  return res;
}

void solve(){
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> a[i];
  }
  for(int it=1;it<=n;it++){
  

    int cnt1=0,cnt3=0;
    for(int i=1;i<=n;i++){
      if(a[i] == a[it])b[i] = 2;
      else if(a[i] < a[it])b[i]=1,cnt1++;
      else b[i]=3,cnt3++;
    }

    if(cnt1 > cnt3){
      for(int i=1;i<=n;i++){
        if(b[i]==1)b[i]=3;
        else if(b[i]==3)b[i]=1;
      }
      swap(cnt1,cnt3);
    }

    assert(cnt1 <= cnt3 and (cnt1%2) == (cnt3%2));
    
    vi v1;
    for(int i=1;i<it;){
      int cur = b[i];
      int qtd=0;
      while(i < it and b[i]==cur){
        qtd++;
        i++;
      }

      if(cur == 3){
        while(qtd >= 3){
          qtd-=2;
          cnt3-=2;
        }
      }
      for(int j=0;j<qtd;j++)
        v1.pb(cur);
    }

    cnt3-=go(v1);
    v1.clear();
    for(int i=it+1;i<=n;){
      int cur = b[i];
      int qtd=0;
      while(i <=n and b[i]==cur){
        qtd++;
        i++;
      }
      if(cur == 3){
        while(qtd >= 3){
          qtd-=2;
          cnt3-=2;
        }
      }
      for(int j=0;j<qtd;j++)
        v1.pb(cur);

    }

    cnt3-=go(v1);

    cout << (cnt3<=cnt1);
  }
  cout << endl;
}

int32_t main(){
  fastio;
  int t;
  cin >> t;
  while(t--){
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
