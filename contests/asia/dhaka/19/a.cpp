// upsolving
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
#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left sefude
//#define right sefudermano
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

const int MAGIC = 82;
const int MAXSUM = MAGIC * MAGIC/2;
int dp[MAGIC][MAXSUM][MAGIC];

const int inf = 1e7 + 100;
int add(int a,int b){
  int c = min(inf,a+b);
  return c;
}

// used i first terms, sum == j, used K elements
void init(int n){


  int maxsum = (n*(n+1))/2;

  dp[0][0][0] = 1;
  for(int i=1;i<=n;i++){

    for(int j=0;j<=maxsum;j++){
      for(int k=0;k<=n;k++){
        dp[i][j][k] = dp[i-1][j][k];
        if(k>0 and j-i>=0){
          // put me inside ;)
          dp[i][j][k] = add(dp[i][j][k],dp[i-1][j-i][k-1]);
        }
      }
    }
  }


}

int n;

void QUERY(){
  int m,k;
  cin >> m>>k;
  k--;
  n = min(m,MAGIC - 2);

  vector<pii> order;
  int mx = (n *(n+1))/2;
  for(int i=1;i<=mx;i++){
    for(int j=1;j<=n;j++){
      if(gcd(i,j)==1)order.pb(pii(i,j));
    }
  }

  sort(all(order),[&](pii a,pii b){
    return 1ll * a.ff * b.ss < 1ll * b.ff * a.ss;
  });

  for(int i=0;i<sz(order) - 1;i++){
    pii a= order[i],b = order[i+1];
    assert(a.ff * b.ss < b.ff * a.ss);
  }

  const int maxsum = (n*(n+1))/2;

  for(auto it : order){
    int sum = it.ff,qtd = it.ss;
    int mul = 1;
    int flag=0;
    for(;mul*qtd<=n and sum * mul<=maxsum;mul++){
      int cur = dp[n][sum*mul][mul*qtd];

      if(k>=cur){
        k-=cur;
      }else{
        flag = 1;
        break;
      }   
    }

    if(flag){

      // here hell yeah
      int num = mul * qtd;
      int s = sum * mul;
      vi res; 
     
      map<int,int> mp;
      for(int i=1;i<=n;i++){
        mp[i] = m-i+1;
      }
      for(int i=n;i>=1;i--){
        int cur = dp[i-1][s-i][num-1];
        if(k>=cur){
          k-=cur;
          continue;
        }
        s-=i;
        num--;
        res.pb(i);
      }
      assert(k == 0 and sz(res)!=0);

      for(int& x : res)x = mp[x];
      sort(all(res));
   

      for(int x : res){
        cout << x <<" ";
      }
      cout << endl;
      
      return; 

    }

  }

}


int32_t main(){
  fastio;
  int t;
  cin>>t;
  int T = t;
  int cs=0;
  init(MAGIC - 2);
  while(t--){
    cs++;
    cout <<"Case "<<cs<<": ";
    QUERY();
  }




  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
