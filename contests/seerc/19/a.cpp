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

const int N = 200100;
int lazy[4*N];

int sumz=0;
int len[N],p[N];
void build(int no,int i,int j){
    lazy[no] = -1;
  if(i == j){
    p[i] = i,len[i] = 1;
    return;
  }
  int mid = (i+j)>>1;
  build(2*no,i,mid);build(2*no+1,mid+1,j);
}

void flush(int no,int i,int j){
  if(lazy[no] == -1)return;
  if(i == j)p[i] = lazy[no];

  if(i!=j){
    int l = no<<1,r=no<<1|1;
    lazy[l] = lazy[r] = lazy[no]; 
  }
  lazy[no] = -1;
}

void Set(int no,int i,int j,int a,int b,int val){
  flush(no,i,j);
  if(i > j || i > b || j < a)return;
  if(a<=i and j<=b){
    lazy[no] = val;
    flush(no,i,j);
    return;
  }
  int mid = (i+j)/2;
  int l = no<<1,r=no<<1|1;
  Set(l,i,mid,a,b,val);
  Set(r,mid+1,j,a,b,val);
}

int n,m;
int a[N];
void go(int no,int i,int j,int p){
  flush(no,i,j);
  if(i == j)return;
  int mid = (i+j)>>1;
  int l = no<<1,r=no<<1|1;
  if(p<=mid)return go(l,i,mid,p);
  return go(r,mid+1,j,p);
}
void go(int p){
  return go(1,1,n,p);
}
void upd(int pos,int val){
  go(pos);

  if(val == 0){

    if(p[pos] + len[p[pos]] -1 == pos){
      // termina aqui
      sumz -= (len[p[pos]])/2;
      sumz += (len[p[pos]] - 1)/2;
      
      len[p[pos]]--;
      // OK
    }else{
      // eu divido no meio:
      sumz -= (len[p[pos]])/2;
      int len1 = pos - p[pos];
      int len2 = p[pos] + len[p[pos]]-1 - pos;
      sumz += (len1/2) + (len2/2);
      int fim = p[pos] + len[p[pos]] - 1;
      if(pos+1<=fim){
        Set(1,1,n,pos+1,fim,pos+1);
      }
      if(pos+1<=fim)len[pos+1] = len2;
      len[p[pos]] = len1;
    }
    p[pos] = pos,len[pos] = 0;
    a[pos] = 0;
    return;
  }
  // val == -1
  a[pos] = -1;
  len[pos] = 1,p[pos] = pos;

  if(pos < n and a[pos + 1] == 1){
    go(pos+1);
    // try to merge with next:
    sumz+=(len[pos+1] + 1)/2 - (len[pos+1]/2);
    Set(1,1,n,pos+1,pos+len[pos+1],pos);
    len[pos] = len[pos+1] + 1;
    len[pos+1] = 0;
  }
  if(pos > 1 and a[pos-1] == 1){
    go(pos-1);
    // merge with last
    sumz+=(len[p[pos-1]] + len[pos])/2;
    sumz-=((len[p[pos-1]]/2) + (len[pos]/2));
    Set(1,1,n,pos,pos + len[pos]-1,p[pos-1]);
    len[p[pos-1]] = len[p[pos-1]] + len[pos];
    len[pos]=0;
    go(pos);
    assert(p[pos] == p[pos-1]);
  }

}


vi here[N];
int res[N];
int32_t main(){
  fastio;
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin >> a[i];
    here[a[i]].pb(i);
    a[i] = 1;
  } 
  build(1,1,n);
  for(int i=1;i<=m;i++){
    if(sz(here[i]) == 0){
      cout << -1 <<" \n"[i==m];
      continue;
    }
    for(auto it : here[i])upd(it,0);
    res[i] = n - sz(here[i]) + sumz;
    if(a[1] == 0 || a[n] == 0 || a[1]==a[n]){
      // ok
    }
    else{//merge
      go(n);
      int len1 = len[1];
      int len2 = len[p[n]];
      res[i] = res[i] - (len1/2) - (len2/2) + ((len1 + len2)/2);
    }
    for(auto it : here[i])upd(it,-1);
    cout << res[i]<<" \n"[i==m];
  }

  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
