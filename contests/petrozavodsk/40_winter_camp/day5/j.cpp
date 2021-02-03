#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
using namespace std;


const int N = 505;
int a[N],b[N];

typedef array<int,3>arr;

int32_t main(){
  fastio;
  int n;
  cin >> n;
  for(int i=1;i<=n;i++){
    cin >> a[i];
  }
  for(int i=1;i<=n;i++){
    cin >> b[i];
  }
  sort(a+1,a+1+n);
  vector<arr> resp;
  resp.pb({1,n,0});

  for(int i=1;i<n;i++){
    int need = b[i];
    int mx=0,mn = 1e9,here=0;
    for(int j = i;j<=n;j++){
      mx = max(mx,a[j]);
      mn = min(mn,a[j]);
      if(a[j] == need){
        here = j;
        break;
      }
    }

    if(here == i)continue;
    if(mx == need){
      resp.pb({i,here,1});
      sort(a+i,a+1+here,greater<int>());
    }else{
      assert(mn == need);
      resp.pb({i,here,0});
      sort(a+i,a+1+here);
    }
    assert(a[i] == b[i]);
  }
  cout << resp.size() <<endl;
  for(auto it : resp){
    cout << it[0]<<" "<<it[1]<<" "<<(it[2]==0 ? "I" : "D")<<endl;
  }
}
