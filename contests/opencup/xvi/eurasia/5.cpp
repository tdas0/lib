#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
#define ff first
#define ss second
#define pb push_back
typedef vector<int> vi;
const int N = 1605;

pii p[N];
int a[N];

double T = 0;
vi ans;


int n,m,k,vb,vc;

ll sq(ll x){
  return x * x;
}

double dist(int i,int j){
  return sqrt(sq(p[i].ff - p[j].ff) + sq(p[i].ss - p[j].ss));
}

int pai[N];
const int inf = 1e9;
double d[N];
double g[N][N];
int vis[N];
bool inq[N];


typedef pair<double,int> pdi;

double DJ(int s,int t){
  for(int i=1;i<=n;i++){
    d[i] = inf;
    pai[i] = -1;
    vis[i] = 0;
  }

 // priority_queue<pdi,vector<pdi>,greater<pdi> > q;
  d[s] = 0;
//  q.push(pdi(d[s],s));
  
  while(true){
    int cur ;//= q.top().ss;
    //q.pop();
    double opt = inf;
    for(int i = 1; i <= n; i++){
      if(vis[i]) continue;
      if(d[i] < opt){
        cur = i;
        opt = d[i];
      }
    }
    if(vis[cur])continue;
    vis[cur] = 1;
    if(cur == t)break;

    for(int to = 1;to<=n;to++){
      double Dcor = g[cur][to];
      if(d[to] > d[cur] + Dcor){
        d[to] = d[cur] + Dcor;
        pai[to] = cur;
       // q.push(pdi(d[to],to));
      }
    }

  }

  return d[t];

}

void go(int s,int t,bool ini = 0){
  double best = DJ(s,t);

  vi path;
  int cur = t;

  while(cur!=s){
    path.pb(cur);
    cur = pai[cur];
  }
  reverse(path.begin(),path.end());
  if(ini){
    ans.pb(s);
  }

  for(int i=0;i<(int)path.size();i++){
    int x = path[i];
    if(x!=s)ans.pb(x);
  }


  T+=best;
}


int main(){

  scanf("%d%d%d%d%d",&n,&m,&k,&vb,&vc);
  //cin>>n>>m>>k>>vb>>vc;
  for(int i=1;i<=n;i++){
    scanf("%d%d",&p[i].ff,&p[i].ss);
    //cin >> p[i].ff >> p[i].ss;
  }

  for(int i=1;i<=n;i++){
    for(int j=1;j<i;j++){
      g[i][j] = g[j][i] = (1.0  * dist(i,j) / (1.0 * vc));
    }
  }

  for(int i=0;i<m;i++){
    int a,b;
    //cin>>a>>b;
    scanf("%d%d",&a,&b);
    g[a][b] = g[b][a] = (1.0 * dist(a,b)/(1.0 * vb));
  }
  for(int i=0;i<k;i++){
    scanf("%d",&a[i]);
    //cin >> a[i] ;
  }


  go(1,a[0],1);
  a[k] = n;
  for(int i=0;i<k;i++){
    go(a[i],a[i+1]);
  }
  
  printf("%.8lf\n",T);
  for(int i=0;i<sz(ans);i++){
    int x = ans[i];

    printf("%d",x);
    if(i == sz(ans)-1)printf("\n");
    else printf(" ");
  }


}
