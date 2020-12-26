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
//#define left oooooopss
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


const int N = 18;
int a[N][N];
int dp[(1<<N)+1][N][N][2];

int n;
inline int in(int a,int S){
  return !!(S&(1<<a));
}
int F;
int solve(int S,int u,int v,int b){
  if(S == F and u==v and b == 1)return 0;
  int &x = dp[S][u][v][b];
  if(x!=-1)return x;
  x = 1e9;

  if(u == v  and b==1){

    rep(a,0,n){
      rep(b,0,n){
        
        if(in(a,S) and in(b,S)){
          x=min(x,solve(S,a,b,0));
        }

      }
    }

    return x;
  }
  if(b and a[u][v]!=-1){
    x = a[u][v];
    if(S != F)x+=solve(S,u,u,1);
  }
  rep(w,0,n){
    if(!in(w,S) and a[u][w]!=-1){
      int cur = a[u][w] + solve(S|(1<<w),w,v,(u == v) ? 0 : 1);
      x = min(x,cur);
    }
  }
  return x;
}
void roll(int S,int u,int v,int b){
  cout <<S<<" "<< u<<" "<<v<<" "<<b<<endl;
  if(u==v and b){
    if(S==F)return;
    int x = solve(S,u,v,b);
    rep(a,0,n){
      rep(b,0,n){
        
        if(in(a,S) and in(b,S)){
          if(x == solve(S,a,b,0)){
            roll(S,a,b,0);
            return;
          }
        }

      }
    }
  }
  int x = solve(S,u,v,b);
  if(b and a[u][v]!=-1){
    cout<<"FIM"<<endl;
    return;
  }
  rep(w,0,n){
    if(!in(w,S) and a[u][w]!=-1){
      int cur = a[u][w] + solve(S|(1<<w),w,v,(u == v) ? 0 : 1);
      if(x == cur){
        roll(S|(1<<w),w,v,(u==v)?0:1);
        return;
      }
    }
  }
}


int32_t main(){
  fastio;
  cin >> n;
  F = (1<<n)-1;

  rep(i,0,n)rep(j,0,n){
    cin >> a[i][j];
  }
  int res=0;
  ms(dp,-1);

  /*rep(i,0,(1<<N))rep(j,0,N)rep(k,0,N)rep(b,0,2){
    dp[i][j][k][b] = (int)1e9;
  }
  */
  rep(i,0,n)rep(j,i+1,n){
    if(a[i][j]!=-1){
      int x = min(a[i][j],a[j][i]);
      res+=x;
      a[i][j]-=x;
      a[j][i]-=x;
    }
  }
  int mn=1e9;
  rep(i,0,n){
    mn = min(mn,solve((1<<i),i,i,0));
  }
  res+=mn;
  if(res >= (int)1e9){
    cout<<-1<<endl;
    return 0;
  }
  cout << res << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
