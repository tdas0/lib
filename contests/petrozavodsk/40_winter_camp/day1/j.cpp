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
#define int long long  
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
const int N = 510;
ll w[N*N];
int l[N*N];
multiset<ll> best[N*N];
int qtd[N*N];
map<int,int> tams;
int v[N][N],p[N][N];

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void tira(int id){
  if(qtd[id]==0)return;
  best[l[id]].erase(best[l[id]].find(w[id]));
  tams[l[id]]--;
  if(tams[l[id]]==0)tams.erase(l[id]);
}
void bota(int id){
  if(qtd[id]==0)return;
  best[l[id]].insert(w[id]);
  tams[l[id]]++;
}

int n;
int ok(int l,int c){
  return min(l,c)>=0 and max(l,c)<n;
}
void solve(){
  cin >> n;
  tams.clear();
  rep(i,0,n*n + 10){
    w[i]=0;
    l[i]=0;
    qtd[i]=0;
    best[i].clear();
  }
  rep(i,0,n)rep(j,0,n){
    cin >> v[i][j];
  }
  rep(i,0,n)rep(j,0,n){
    cin >> p[i][j];
    qtd[p[i][j]]++;
  }

  rep(i,0,n){
    rep(j,0,n){
      w[p[i][j]]+=v[i][j];
      rep(k,0,4){
        int L = dx[k] + i;
        int C = dy[k]+j;
        if(ok(L,C) and p[L][C]!=p[i][j])l[p[i][j]]++;
      }
    }
  }

  rep(i,0,n*n + 1){
    bota(i);
  }
  int q;
  cin >> q;
  vector<ll> vec;
  while(q--){
    int i,j,P;
    ll A,B,C;
    cin >> i >> j >> P >> A >> B >> C;
    i--;j--;

  
    tira(P);
    qtd[P]++;
    w[P]+=v[i][j];
    bota(P);

      for(int k=0;k<4;k++){
        int L = i + dx[k];
        int C = j + dy[k];
        
        if(ok(L,C)){
          if(p[L][C]!=p[i][j]){
            tira(p[i][j]);
            l[p[i][j]]--;
            bota(p[i][j]);
            //
            tira(p[L][C]);
            l[p[L][C]]--;
            bota(p[L][C]);
          }
          if(p[L][C]!=P){
            tira(P);
            l[P]++;
            bota(P);
            //
            tira(p[L][C]);
            l[p[L][C]]++;
            bota(p[L][C]);
          }

        }


      }

      tira(p[i][j]);
      w[p[i][j]]-=v[i][j];
      qtd[p[i][j]]--;
      bota(p[i][j]);
      
      p[i][j] = P;
    

    ll res=-LLONG_MAX;
    for(auto it : tams){
      int T = it.ff;
      ll mn = *best[T].begin() , mx = *best[T].rbegin();
      res = max(res,B * T + max(mn * (A+C*T),mx * (A+C*T)));
    }
    vec.pb(res);
  }
  for(int i=0;i<sz(vec);i++){
    cout << vec[i]<<" \n"[i==sz(vec)-1];
  }
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
