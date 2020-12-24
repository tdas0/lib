#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;
typedef pair<int,int> pii;

const int N = 2020;
vector<pii> g[N];
int n;
vector<int> DJ(int S){
	vector<int> dist(n + 1),vis(n+1);
	for(int i=1;i<=n;i++){
		dist[i] = 1e9;
		vis[i] = 0;
	}

	dist[S] =0 ;
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	pq.push(pii(0,S));
	while(!pq.empty()){
		int cur = pq.top().ss;
		pq.pop();
		


		vis[cur] = 1;
		for(auto to : g[cur]){
			if(dist[cur] + to.ss < dist[to.ff]){
				dist[to.ff] = dist[cur] + to.ss;
				if(!vis[to.ff]){
					pq.push(pii(dist[to.ff],to.ff));
				}
			}
		}
	}
	return dist;
}

void solve(){
	int m,t;
	int s,gg,h;
	cin>>n>>m>>t;
	cin>>s>>gg>>h;
	for(int i=1;i<=n;i++){
		g[i].clear();
	}
	int dist=0;
	for(int i=0;i<m;i++){
		int a,b,d;
		cin>>a>>b>>d;
		g[a].pb(pii(b,d));
		g[b].pb(pii(a,d));
		if(a == gg and h==b)dist = d;
		else if(a==h and b==gg)dist = d;
	}
	set<int> S;
	for(int i=0;i<t;i++){
		int x;
		cin>>x;
		S.insert(x);
	}

	vector<int> ds = DJ(s),dh = DJ(h),dg = DJ(gg);

	set<int> ans;
	for(int x : S){
	//	cout << x<<" "<<ds[x]<<" "<<ds[gg]<<" "<<dist<<" "<<dh[x] << endl;
		int op1 = ds[gg] + dist + dh[x];
		int op2 = ds[h] + dist + dg[x];
		if(ds[x] == op1 or ds[x] == op2)ans.insert(x);
	}
	for(int x : ans)cout<<x<<" ";
		cout << endl;
}

int main(){
	fastio;
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}