#include <bits/stdc++.h>
using namespace std;
#define sz(x) (x).size()
const int N = 100005;
typedef vector<int> vi;
vi g[N];
int dg[N] , cycle[N] , cost[N];
bool vis[N];
void clear(int n){
	for(int i = 1; i <= n; i ++){
		g[i].clear();
		vis[i] = false;
		dg[i] = 0 , cycle[i] = 0, cost[i] = 0;
	}
}

void dfs(int x , vi & ans){
	vis[x] = true;
	ans.push_back(cost[x]);
	for(auto w : g[x]){
		if(cycle[w] && !vis[w]){
			dfs(w,ans);
		}
	}
}

int solve(){
	int n;
	scanf("%d" , &n);
	int ans = 0;
	for(int i = 0 ;i < n ; i ++){
		int x , y;
		scanf("%d%d" , &x , &y);
		g[x].push_back(y);
		g[y].push_back(x);
		dg[x] ++ , dg[y] ++;
	}
	queue<int> q;
	for(int i = 1 ; i <= n; i ++){
		if(dg[i] == 1){
			cost[i]++;
			q.push(i);
		}
	}
	while(sz(q)){
		int u = q.front();
		q.pop();
		for(auto w : g[u]){
			dg[w]--;
			cost[w] += cost[u];
			if(dg[w] == 1)
				q.push(w);
		}
	}
	int sumtot = 0;
	int mx = (int) 1e9;
	vi sum;
	int qlqr = 0;
	for(int i = 1; i <= n; i ++){
		if(dg[i] == 2){
			cycle[i] = true;
			sumtot += cost[i];
			mx = min(mx , cost[i]);
			qlqr = i;
		}
	}
	dfs(qlqr, sum);
	for(int i = 0 ; i < (int) sz(sum); i ++){
		ans = max(ans , sumtot + 2 - sum[i] - sum[(i+1)%sz(sum)]);
	}
	ans = max({ans , sumtot, sumtot - mx + 1});
	clear(n);
	return max(3,  ans);
}


int32_t main(){
	int t;
	scanf("%d" , &t);
	for(int _t = 0 ; _t < t; _t++){
		printf("%d\n" , solve());
	}
}
