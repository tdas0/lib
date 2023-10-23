#include <bits/stdc++.h>
#define pb push_back
#define sz(v) ((int)v.size())
using namespace std;
#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define all(X) begin(X), end(X)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


set<ll> res;
ll n;

int is_palin(vector<ll> v){
    rep(i,0,sz(v))if(v[i]!=v[sz(v)-1-i])return 0;
    return 1;
}

void test(ll b){
    if(b<=1)return;
    vector<ll> v;
    ll x = n;
    while(x > 0){
        v.pb(x % b);
        x/=b;
    }
    if(is_palin(v)){
        res.insert(b);
        return ;
    }

}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  cin >> n;
  test(n-1);
  for(ll d = 1; d * d <= n; d++){
    if(n %d == 0){
        test(n/d - 1);
        test(d-1);
    }
    test(d);
  }
    if(sz(res)==0){
        cout << "*" << endl;
        return 0;
    }
    for(auto it : res)cout << it<<" ";
    cout << endl;
}
