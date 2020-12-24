#include <bits/stdc++.h>
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
ll modpow(ll b, ll e ,ll mod) { ll ans = 1;for (; e; b = b * b % mod, e /= 2){if (e & 1) ans = ans * b % mod;}return ans;}
string a , b;
int dp[100020][20];
int vis[100020][20];
int tempo=0;
int solve(int i  ,int j){
 if(i == sz(a) or j == sz(b)){
 	return sz(a)-i + sz(b)-j;
 }
 if(abs(i-j) > 4){
  return 4;
 }
 if(vis[i][j-i+5] == tempo) return dp[i][j-i+5];
 vis[i][j-i+5] = tempo;
 int p = 4;
 p = min({p , solve(i+1, j) + 1 , 1 + solve(i+1, j+1) , 1 + solve(i , j+1)});
 if(a[i] == b[j]) p = min(p, solve(i+1,j+1)); 
 return dp[i][j-i+5] = p;
}

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
 int t;
 cin >> t;
 while(t--){
 	tempo ++;
  cin >> a >> b;
  int p = solve(0,0);
  if(p == 0){
   cout <<"You're logged in!\n";
  }
  else if(p ==1){
   cout<<"You almost got it. You're wrong in just one spot.\n";
  }
  else if(p ==2){
   cout<<"You almost got it, but you're wrong in two spots.\n";
  }
  else if(p ==3){
   cout<<"You're wrong in three spots.\n";
  }
  else{
   cout<<"What you entered is too different from the real password.\n";
  }
 }  
}