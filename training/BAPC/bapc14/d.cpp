#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
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
const int N = 100005;
int go[N][4];
bool vis[N][4];
void dfs(int x , int y){
	vis[x][y] = true;
	rep(j,0,4){
		if(x == go[go[x][y]][j]){
			if(!vis[go[x][y]][(j+2)%4]){
				dfs(go[x][y] , (j+2)%4);
			}
		} 
	}
}
void solve(){
	int n , g;
	cin >> n >> g;
	rep(i,1,n+1){
		rep(j,0,4) cin >> go[i][j], vis[i][j] = false;
	}
	rep(j,0,4){
		dfs(g , j);
	}
	int ans = 0;
	rep(i,1,n+1){
		rep(j,0,4){
			if(!vis[i][j]) dfs(i,j) , ans++;
		}
	}
	cout << ans / 2 << endl;
	return ;
}

int32_t main(){
	int T;
	cin >> T;
	while(T--) solve();	
}