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
#define left oooooopss
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


struct bipartite_match{ // 1 indice
  int n , m;
  vector<vi> g; vi vis , match;
  bipartite_match(int n , int m) : n(n) , m(m), vis(n+m+2) , match(n+m+2) , g(n+m+2){}
  void addLR(int x , int y){ // aresta da esquerda pra direita
    g[x].push_back(y + n);
    return ;
  }
  void addRL(int x , int y){ // aresta da direita pra esquerda
    g[x+n].push_back(y);
    return ;
  }
  bool dfs(int x){
    allin(w,g[x]){
      if(vis[w]) continue;
      vis[w] = true;
      if(match[w] == 0 || dfs(match[w])){
        match[w] = x, match[x] = w; 
        return true;
      }
    }
    return false;
  }
  int solve(){
    int ans = 0; bool haspath;
    do{
      haspath = false;
      fill(all(vis) , false);
      for(int i = 1 ; i<= n + m; i ++){
        if(!match[i] && dfs(i)) haspath = 1 , ans ++ ;
      }
    } while(haspath);
    return ans;
  }
  int matchL(int x){return (match[x] ? match[x] - n : 0);}
  int matchR(int x){return match[x+n];}
};

const int N = 2550 * 3;
ll a[N],b[N];
int32_t main(){
  fastio;
  int n;
  cin>>n;
  vector<ll> cmp;
  for(int i=0;i<n;i++){
    cin >> a[i] >> b[i];
    cmp.pb(a[i] + b[i]);
    cmp.pb(a[i] - b[i]);
    cmp.pb(a[i] * b[i]);
  }
  Unique(cmp);
  bipartite_match M(n,sz(cmp) + 10);
  for(int i=0;i<n;i++){
    int s = lower_bound(all(cmp),a[i] + b[i])-cmp.begin();
    int sub = lower_bound(all(cmp),a[i] - b[i])-cmp.begin();
    int p = lower_bound(all(cmp),a[i] * b[i])-cmp.begin();
    M.addLR(i+1,s+1);
    M.addLR(i+1,sub+1);
    M.addLR(i+1,p+1);
  }
  int tot = M.solve();
  if(tot != n){
    cout<<"impossible"<<endl;
    return 0;
  }
  for(int i=0;i<n;i++){
    char op;
    int id = M.matchL(i+1)-1;
    if(cmp[id] == a[i] + b[i])op = '+';
    else if(cmp[id]==a[i] - b[i])op = '-';
    else if(cmp[id] == a[i] * b[i])op = '*';
    cout << a[i]<<" "<<op<<" "<<b[i]<<" = "<<cmp[id]<<endl;
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
