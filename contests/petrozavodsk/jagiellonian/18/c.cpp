// upsolving
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
const int N = 200005;

int get_int(){
  int a = 0;
  scanf("%d" , &a);
  return a;
}

int n , t , dp[N] , bit[N];  

void add(int x , int v){
  for(int i = x; i < N ; i += (i&-i)){
    bit[i] = max(bit[i] , v);
  }
}
void clear(int x){
  for(int i = x; i < N ; i += (i&-i)){
    bit[i] = 0;
  }
}

int get(int x){
  if(x <= 0) return 0;
  int s = 0;
  for(int i = x ; i > 0 ; i -= (i&-i)){
    s = max(s, bit[i]);
  }
  return s;
}

#define left kasdkas
#define right aksdkakds


void solve( vector < array<int, 3 > > &a){
  int mid = sz(a) / 2;
  if(sz(a) == 0){
    return ;
  }
  if(sz(a) == 1){
    dp[a[0][2]] = max(dp[a[0][2]] , 1);
    return ; 
  }
  vector< array<int, 3 > >  left , right;
  for(int j = 0 ; j < mid ; j ++){
    left.push_back(a[j]);
  }
  for(int j = mid ; j < sz(a); j ++){
    right.push_back(a[j]);
  }
  solve(left);
  vi tob;
  for(auto w : a){
    tob.push_back(w[1]);
  }
  sort(all(tob));
  tob.resize(unique(all(tob)) - begin(tob));
  int pt = 0;
  vector<array<int, 3> > r2 = right;
  sort(all(r2));
  for(auto w : r2){
    while(pt < sz(left) && left[pt][0] < w[0]){
      int pos = lower_bound(all(tob) , left[pt][1]) - begin(tob) + 1;
      add(pos , dp[left[pt][2]]);
      pt++ ;
    }
    int pos = lower_bound(all(tob) , w[1]) - begin(tob);
    dp[w[2]] = max(dp[w[2]], 1 + get(pos));
  }
  for(auto w : left){
    int pos = lower_bound(all(tob) , w[1]) - begin(tob) + 1;
    clear(pos);
  }
  solve(right);
  merge(begin(left) , end(left) , begin(right) , end(right) , begin(a));
}


int32_t main(){
  t = get_int();
  while(t--){
    n = get_int();
    vector< array<int, 3> >  a(n);
    rep(i,0,n) a[i][0] = get_int() , dp[i] = 0 ;
    rep(i,0,n) a[i][1] = get_int() , a[i][2] = i ;
    int ans = 0;    
    solve(a);
    rep(i,0,n)
      ans = max(ans , dp[i]);
    printf("%d\n" , ans);
  }
}

/* clever stuff:
  * int overflow, array bounds
  * special cases (n=1?)
  * do smth instead of nothing and STAY ORGANIZED
  * Keep it simple stupid
  * WRITE STUFF DOWN
  * math -> gcd / lcm / divisors? 
*/
