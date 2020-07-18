#include <bits/stdc++.h>
using namespace std;
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef array<int,3> arr;
typedef vector<int> vi;
const int N = 100005;
vi g[2*N];
bool vis[2*N];
int n , m;
bool can = true;
vector<arr> ans;
vector<int> open[2*N];
bool ismatched[2*N];
int fr = 0;
void solve(int x){
	vis[x] = true;
	fr ^= 1;
	vector<int> tv;
	allin(w, g[x]){
		if(!vis[w]) solve(w) , tv.push_back(w);
	}
	allin(w,tv){
		if(sz(open[w])){
			ans.push_back({open[w].back() , x , w});
			ismatched[open[w].back()] = true;
			open[w].pop_back();
			if(sz(open[w])) can = false;
			ismatched[x] =1;
		}
		if(!ismatched[w]){
			open[x].push_back(w);
		}
	}
	while(open[x].size() >= 2){
		int u = open[x].back() ; open[x].pop_back();
		ismatched[u] = 1 , ismatched[open[x].back()] = 1;
		ans.push_back({u , open[x].back() , x});
		open[x].pop_back();
	}
	if(open[x].size() && !ismatched[x]){
		ans.push_back({open[x].back() , x , -1});
		ismatched[open[x].back()] = true;
		open[x].pop_back();
		ismatched[x] = true;

	}
}

int32_t main(){
	cin >> n >> m;
	n *= 2;
	for(int i = 0 ; i < m ; i ++ ){
		int x , y;
		cin >> x>> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i = 0 ; i < n; i ++){
		if(!vis[i]){
			fr = 0  ;
			solve(i);
			if(fr) can = false;
		}
	}
	if(!can) cout <<"IMPOSSIBLE" << endl;
	else{
		cout <<"POSSIBLE" << endl;
		for(int i = 0 ; i < sz(ans) ; i ++){
			cout << ans[i][0] <<" " << ans[i][1] <<" " << ans[i][2] << endl;
		}
	}
}