#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
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
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
const int N = 100100;
const int sq = 450;

const int NUM_BLCK = 10 + N/sq;
int n , q , a[N] , sz[NUM_BLCK+2];
pii block[NUM_BLCK][sq+2];


ll pref[NUM_BLCK+2][sq+2];
ll ans[NUM_BLCK+2][NUM_BLCK+2];
ll pre[N][NUM_BLCK+2];

pii p1[2][N],p2[2][N];
int sz1[2],sz2[2];
ll Pre[2][N];

ll brute(int l1,int r1,int l2,int r2){
  ll r=0;
  for(int i=l1;i<=r1;i++){
    for(int j=l2;j<=r2;j++)
      r+=abs(a[i]-a[j]);
  }
  return r;
}

int cnt[NUM_BLCK];
ll sum[NUM_BLCK];

int32_t main(){
  scanf("%d%d" , &n , &q);
  for(int i = 0 ; i < n; i ++){
    scanf("%d" , &a[i]);
    block[i/sq][sz[i/sq]++] = pii(a[i],i);
  }
  
  for(int i = 0 ; i <= (n-1)/sq ; i ++){
    sort(block[i] , block[i] + sz[i]);
    for(int j = 0 ; j < sz[i];  j ++){
      pref[i][j] = block[i][j].ff;
      //cout << i<<" "<<j<<" "<<pref[i][j]<<endl;
      if(j)
        pref[i][j] += pref[i][j-1];
    }
  }
  for(int i = 0 ; i <= (n-1)/sq ; i ++){
    for(int j = 0 ; j <= (n-1)/sq ; j ++){
      ll l = 0;
      for(int k = 0 ; k < sz[i] ; k ++){
        while(l < sz[j] && block[j][l].ff <= block[i][k].ff){
          l++;
        }
        ans[i][j] += ((1ll*l)*(1ll*block[i][k].ff)) - (l ? pref[j][l-1] : 0)
                - ((1ll*(sz[j] - l)) * (1ll*block[i][k].ff)) + (pref[j][sz[j] - 1] - (l ? pref[j][l-1] : 0)); 

      }
      if(j)
       ans[i][j] += ans[i][j-1]; 
    }
  }

  vector<pii> order;
  rep(i,0,n)order.pb(pii(a[i],i));
  rep(i,0,(n-1)/sq + 1)
    cnt[i]=0,sum[i]=0;

  sort(all(order));
  for(auto it : order){
    int id = it.ss;
    cnt[id/sq]++;sum[id/sq]+=a[id];
    for(int j=0;j<=(n-1)/sq;j++){
      pre[id][j]+= 1ll*cnt[j]*a[id] - sum[j];
    }
  }
  rep(i,0,(n-1)/sq + 1)
    cnt[i]=0,sum[i]=0;
  reverse(all(order));
  for(auto it : order){
    int id = it.ss;
    cnt[id/sq]++;sum[id/sq]+=a[id];
    for(int j=0;j<=(n-1)/sq;j++){
      pre[id][j]+= sum[j] - 1ll*cnt[j]*a[id];
    }
  }
  rep(i,0,n)
    rep(j,1,(n-1)/sq + 1)
      pre[i][j]+=pre[i][j-1];

  auto get = [&](int l,int r){
    int lx = (l+sq-1)/sq;
    int rx = (r+1)/sq - 1;
    if((rx+1)*sq - 1 < l)rx--;
    return pii(lx,rx);
  };


  auto generate = [&](int& SZ,pii P[],int l,int r,int bk,ll PRE[]) ->void{
    SZ=0;
    if(bk < 0)return;
    for(int j=0;j<sz[bk];j++){
      if(l<=block[bk][j].ss and block[bk][j].ss<=r){
          P[SZ] = block[bk][j];
          PRE[SZ] = P[SZ].ff;
          if(SZ)
            PRE[SZ]+=PRE[SZ-1];
          SZ++;
      }
    }
  };

  while(q--){
    int l1,r1,l2,r2;

    scanf("%d%d%d%d" , &l1 , &r1 , &l2 , &r2);
    l1 -- , r1 -- ,l2 -- , r2 -- ;


    int lx,rx,ly,ry;
    tie(lx,rx) = get(l1,r1);
    tie(ly,ry) = get(l2,r2);
    ll res=0;
    // block - block
    if(ly<=ry){
      for(int j=lx;j<=rx;j++){
        res+= ans[j][ry] - (ly ? ans[j][ly-1] : 0);
      }
    }
      
    // pedacos ordenados:
    int L=l1/sq,R=r1/sq;
    if(lx == L)
      L=-1;
    if(rx == R || L==R)
      R=-1;
    generate(sz1[0],p1[0],l1,r1,L,Pre[1]);
    generate(sz1[1],p1[1],l1,r1,R,Pre[0]);

    L = l2/sq,R=r2/sq;
    if(ly==L)
      L=-1;
    if(ry==R  || R==L)
      R=-1;

    generate(sz2[0],p2[0],l2,r2,L,Pre[0]);
    generate(sz2[1],p2[1],l2,r2,R,Pre[1]);
  //  cout << L<<" "<<R << endl;
    // bloco - pedaco:

    if(ly<=ry){

      rep(i,0,2){
        rep(j,0,sz1[i]){
         // cout << p1[i][j].ss <<endl;
          res+=pre[p1[i][j].ss][ry] - (ly ? pre[p1[i][j].ss][ly-1] : 0);
        }
       // cout << "new "<<delta<<endl;
      }

    }

    if(lx<=rx){

      rep(i,0,2){
        rep(j,0,sz2[i]){
          res+=pre[p2[i][j].ss][rx] - (lx ? pre[p2[i][j].ss][lx-1] : 0);
        }
      }

    }


    // pedaco - pedaco:

    rep(i,0,2){

      rep(j,0,2){
        if(sz2[j]==0)continue;
        int l = 0;

        rep(k,0,sz1[i]){

          while(l < sz2[j] and p2[j][l].ff < p1[i][k].ff)
            l++;

          res+= 1ll*l*p1[i][k].ff - (l ? Pre[j][l-1] : 0);
          res+= (l!=sz2[j] ? (Pre[j][sz2[j]-1] - (l ? Pre[j][l-1] : 0)) : 0) - 1ll*(sz2[j] - l)*p1[i][k].ff;

        }
      }

    }

    printf("%lld\n",res);
  }

}
// upsolve
