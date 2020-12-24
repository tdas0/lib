#include <algorithm>
#include <iostream>
#include <assert.h>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <bitset>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) (x).begin, (x).end
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
int n;
const int N = 101;
vi g[N];
bool mark[N][N];
 
int to_int(string s){
  int res=0;
  for(int i=0;i<s.size();i++){
    res = 10 * res + (s[i]-'0');
  }
  return res;
}
void get(int& a,int& b,string s){
  string t="";
  a = b = -1;
  int n = s.size();
  for(int i=0;i<s.size();i++){
    while(i<n and s[i]!='-'){
      t+=s[i];
      i++;
    }
    if(a==-1)a = to_int(t);
    else b = to_int(t);
    t="";
  }
}
int cor[N];

bool dfs(int x){
	bitset<5> t = 0;
	for(auto w: g[x]){
		t[cor[w]] = true;
	}	
	for(int j = 1 ; j <= 4;  j ++){
		if(t[j]) continue;
		bool ok = 1;
		cor[x] = j;
		for(auto w : g[x]){
			if(cor[w])continue;
			ok &= dfs(w);
			if(!ok){
				cor[x] = 0;
				break; 
			}
		}
		if(ok) return 1;
	}
	return 0;
}


int32_t main(){
	ios::sync_with_stdio(false);
	cin.tie(0) , cout.tie(0);
	cin >> n;
	string s;
	while(cin >> s){
		int a , b;
		get(a,b,s);
		if(mark[a][b] || mark[b][a]) continue;
		mark[a][b] = 1;
		mark[b][a] = 1;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i = 1 ;i  <= n; i ++){
		if(!cor[i])
			dfs(i);
	}
	for(int i = 1 ;i <= n; i ++){
		cout << i <<" " << cor[i] << endl;
	}
}