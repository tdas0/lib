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

const int N = (1<<20) + 10;
int d[N];
int pai[N];

int f(int x){
  return pai[x]=(pai[x]==x?x:f(pai[x]));
}

bool join(int a,int b){
  a = f(a),b = f(b);
  if(a==b)return 0;
  pai[a] = b;
  return 1;
}

struct edge{
  int a,b,c;
  edge(){}
  edge(int A,int B,int C){
    a = A,b = B,c = C;
  }
  bool operator<(const edge& o) const{
    return c < o.c;
  }
};

int32_t main(){
  fastio;
  int q;
  cin >> q;
  while(q--){
    int n,m;
    cin >> n >> m;
    for(int i=0;i<(1<<n);i++)d[i] = 100000,pai[i] = i;
    queue<int> q;
    for(int i=0;i<m;i++){
      int mask=0;
      for(int i=0;i<n;i++){
        char c;
        cin>>c;
        mask = mask*2 + (c=='L');
      }

      d[mask] = 0;
      pai[mask] = mask;
      q.push(mask);
    }

    while(!q.empty()){
      int cur = q.front();
      q.pop();
      for(int i=0;i<n;i++){
        int other = cur;
        other^=(1<<i);
        if(d[other] > d[cur] + 1){
          d[other] = d[cur] + 1;
          pai[other] = cur;
          q.push(other);
        }
      }
    }

    vector<edge> e;
    for(int i=0;i<(1<<n);i++){
      for(int j=0;j<n;j++){
        if(!(i&(1<<j)))continue;
        if(f(i)!=f(i^(1<<j))){
          e.pb(edge(f(i),f(i^(1<<j)),d[i] + d[i^(1<<j)] + 1));
        }
      }
    }

    sort(all(e));
    ll res = 0;
    for(auto ed : e){
      if(join(ed.a,ed.b)){
        res+=ed.c;
      }
    }

    cout << res << endl;

  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
