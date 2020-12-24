/* upsolving*/
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define pb push_back
#define int long long
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define ff first
#define ss second
const int N = 210;
char mat[N][N];
pii in[N][N];
int prime[N*N];

int vis[N][N];

int dfs(int i,int j){
  if(vis[i][j])return 0;
  vis[i][j] = 1;
  return dfs(in[i][j].ff,in[i][j].ss) + 1;
}

const int M  = 78294349;

void solve(){
  int n,m;
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      cin >> mat[i][j];
      if(mat[i][j]=='#'){
        in[i][j] = pii(i,j);
      }else in[i][j] = pii(-1,-1);
    }
  }

  // go cima
  for(int j=1;j<=m;j++){
    vector<pii> v;
    for(int i=1;i<=n;i++){
      if(in[i][j] != pii(-1,-1)){
        v.pb(in[i][j]);
      }
    }

    int id=0;
    for(int i=1;i<=n;i++){
      if(id<sz(v))in[i][j] = v[id++];
      else in[i][j] = pii(-1,-1);
    }
  }


  // go right:
  for(int i=1;i<=n;i++){
    vector<pii> v;
    for(int j=m;j>=1;j--){
      if(in[i][j]!=pii(-1,-1))v.pb(in[i][j]);
    }
    int id=0;
    for(int j=m;j>=1;j--){
      if(id < sz(v))in[i][j] = v[id++];
      else in[i][j] = pii(-1,-1);
    }

  }


  // go down
  for(int j=1;j<=m;j++){
    vector<pii> v;
    for(int i=n;i>=1;i--){
      if(in[i][j]!=pii(-1,-1)){
        v.pb(in[i][j]);
      }

    }
    int id=0;
    for(int i=n;i>=1;i--){
      if(id < sz(v))in[i][j] = v[id++];
      else in[i][j] = pii(-1,-1);
    }
  }



  // go left
  for(int i=1;i<=n;i++){
    vector<pii> v;
    for(int j=1;j<=m;j++){
      if(in[i][j]!=pii(-1,-1)){
        v.pb(in[i][j]);
      }
    }
    int id=0;
    for(int j=1;j<=m;j++){
      if(id < sz(v))in[i][j] = v[id++];
      else in[i][j] = pii(-1,-1);
    }
  }


  for(int i=0;i<N*N;i++)prime[i]=0;
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      vis[i][j]=0;
//      cout <<"("<<in[i][j].ff<<","<<in[i][j].ss<<") ";
    }
  //  cout << endl;
  }
  for(int i=1;i<=n;i++){
    for(int j=1;j<=m;j++){
      if(vis[i][j] or in[i][j]==pii(-1,-1))continue;
      int val = (dfs(i,j));
      
      for(int k = 2;k*k<=val;k++){
        if(val%k==0){
          int cur=0;
          while(val%k==0){
            cur++;
            val/=k;
          }
          prime[k] = max(prime[k],cur);
        }
      }

      if(val > 1)prime[val] = max(prime[val],1LL);

    }
  }


  ll res=1;

  for(int i=1;i<N*N;i++){
    if(prime[i]==0)continue;

    while(prime[i]--){
      res = res * i %M;
    }
  }
  cout << res << endl;

}


int32_t main(){
    fastio;
    int t;
    cin>>t;
    int cs=0;
    while(t--){
      cs++;
      cout << "Case "<<cs<<": ";
      solve();
    }
}
