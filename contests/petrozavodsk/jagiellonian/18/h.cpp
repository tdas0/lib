// upsolving
#include <bits/stdc++.h>
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;

const int N = 100100;
int r[N],c[N];

void upd(pii x,int v){
  r[x.ff]+=v;
  c[x.ss]+=v;
}

const int M = 1e9 + 7;

void solve(){

  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> r[i];
  }
  for(int i=1;i<=n;i++){
    cin >> c[i];
  }

  pii a=pii(1,1),b=pii(1,1);//both start at 1,1
  int ans = 1;
  for(int d = 0;d < 2 * n - 1 ; d ++ ){
    upd(a,-1);upd(b,-1);
    if(a==b)upd(a,+1);

    if(a.ff > n or a.ss > n or b.ff > n or b.ss > n){
      cout << 0 << endl;
      return;
    }
    
    if(a == b){
      // go together or split
      if(r[a.ff] == 0){
        // must go down
        a.ff++;
        b = a;
      }else if(c[a.ss] == 0){
        // must go right
        a.ss++;
        b = a;
      }else{
        a.ff++;
        b.ss++;
        ans = ans * 2ll %M;
      }
    }else{
      // independente
      if(a.ff  < b.ff)swap(a,b);
      if(c[a.ss] > 0){
        // must stay in the row
        a.ff++;
      }else{
        a.ss++;
      }
      if(r[b.ff] > 0){
        b.ss++;
      }else{
        b.ff++;
      }
    }

  }

  for(int i=1;i<=n;i++){
    if(r[i]!=0 or c[i]!=0){
      cout << 0 << endl;
      return ;
    }
  }
  cout << ans << "\n";

}

int32_t main(){
  int q;
  cin >> q;
  while(q--){
    solve();
  }
  // math -> gcd it all
  // Did u check N=1? Did you switch N,M?
}
