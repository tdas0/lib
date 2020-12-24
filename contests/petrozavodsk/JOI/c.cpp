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

const int N = 1010;
int x[N],y[N];
char c[N];
int k,n;
int get(char ch){
  if(ch=='J')return 0;
  if(ch=='O')return 1;
  return 2;
}
struct node{
  int a,b,c;
  node(int a,int b,int c):a(a),b(b),c(c){}
  bool operator<(const node& o)const{
    return tie(a,b,c) < tie(o.a,o.b,o.c);
  }
};
map<node,int> dp;

int solve(int i,int j,int k,vi cur){
  if(dp.count({i,j,k}))return dp[{i,j,k}];
  if(sz(cur) == 0)return 0;
  if(k == 0){
    return 0;
  }

  vector<vi> q(4,vi());//quadrante;
  vector<vi> cnt(4,vector<int>(3,0));
  vi tot(4,0);
  rep(f,0,4){
    rep(cor,0,3)cnt[f][cor]=0;
    q[f].clear();
  }
  
  for(int id : cur){
    int f1 = (x[id]>= i + (1LL<<(k-1)));
    int f2 = (y[id]>= j + (1LL<<(k-1)));
    int pos = (f1<<1) + (f2<<0);
    q[pos].pb(id);
    cnt[pos][get(c[id])]++;
    tot[pos]++;
  }
  int best = sz(cur);
  vi perm;
  for(int i=0;i<4;i++){
    perm.pb(i);
  }
  do{

    // perm[0] -> #
    // perm[1] -> J
    // perm[2] -> O
    // perm[3] -> 1

    int good = 0;
    good+=tot[perm[0]];
    good+=cnt[perm[1]][0] + cnt[perm[2]][1] + cnt[perm[3]][2];
    int ni=i,nj = j;
    if(perm[0]&(1<<1)){
      ni+=(1<<(k-1));
    }
    if(perm[0]&(1<<0)){
      nj+=(1<<(k-1));
    }
    int res = solve(ni,nj,k-1,q[perm[0]]) + sz(cur) - good;
    best = min(best,res);
  }while(next_permutation(all(perm)));  
  dp[{i,j,k}] = best;
  return best;
}

int32_t main(){
  fastio;
  cin >> k >> n;
  vi cur;
  for(int i=1;i<=n;i++){
    cin >> x[i] >> y[i] >> c[i];
    cur.pb(i);
  }

  cout << solve(1,1,k,cur) << endl;
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
