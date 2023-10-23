#include <bits/stdc++.h>
#define pb push_back
using namespace std;
#define rep(i,a,b) for (int i = a; i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n, k;

const int N = 300+15;
vector<int> a (N);
vector<int> cur (N);
vector<vector<int>> nxt (N, vector<int>(N, N));

vector<bool> tak (N);
const int QTD = 10000;
vi order;
mt19937 rng(1238);
int ct=0;

void bt(int i, int p) {
  if (i == k) {
    if(p < n)return;
    for (int j = 0; j < k; j++) { cout << cur[j] << " "; }
    cout << "\n";
    exit(0);
  }
  for(int j = 0; j < k; j++) if(!tak[j]) { 
    if(p >= n || nxt[p][j] > n) {
      cur[i] = j + 1;
      tak[j] = 1;
      bt(i+1, n);
      return;
    }
  }
  shuffle(all(order),rng);
  for (int j : order) if (!tak[j]) {
    tak[j] = 1;
    cur[i] = j+1;
    bt(i+1, nxt[p][j]);
    tak[j] = 0;
  }
}

const int L = 21;
int dp[1<<L];
int pai[1<<L];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  cin >> n >> k;
  rep(i,0,k)order.pb(i);

  for (int i = 0; i < n; i++) { cin >> a[i]; a[i]--;}
  for (int i = n-1; i >= 0; i--) {
    nxt[i] = nxt[i+1];
    nxt[i][a[i]] = i;
  }
  if( k > 20 ){
    bt(0, 0);
    cout <<"*"  << endl;
    return 0;
  }else{

    rep(i,0,(1<<k))dp[i] = -1;
    dp[0] = 0;
    for(int msk=0;msk < (1<<k);msk++){
      // cout << msk <<" " << dp[msk] << endl;
      if(dp[msk] == -1)continue;
      rep(j,0,k)if(!(msk>>j&1)){
        int nmsk = msk|(1<<j);
        int pos = (dp[msk] >= n ? n : nxt[dp[msk]][j]);
        if(dp[nmsk] < pos){
          dp[nmsk] = pos;
          pai[nmsk] = j;
        }
      }
    }
    if(dp[(1<<k)-1] >= n){
      int cur = (1<<k) - 1;
      vi vec;
      while(cur){
        int j = pai[cur];
        vec.pb(j+1);
        cur^=(1<<j);
      }
      reverse(all(vec));
      for(auto p : vec)cout << p<<" ";
      cout << endl;
    }else{
      cout << "*" << endl;
      return 0;
    }
  }
  
}
