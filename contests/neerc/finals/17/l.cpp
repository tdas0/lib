#include <bits/stdc++.h>
#define endl '\n'
#define pb push_back
#define MAXN 100100
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
using namespace std;


vector<int> adj[MAXN];
vector<int> ini[MAXN],fim[MAXN];
int tin[MAXN],tout[MAXN];
int pai[MAXN];
int level[MAXN];
const int MAXL = 20;
int ans[MAXN][MAXL];
int t=0;

void dfs(int v,int p=-1){

	for(int i=0;i<adj[v].size();i++){
		int to = adj[v][i];
		if(to!=p){
			pai[to] = v;
			level[to] = level[v] + 1;
			dfs(to,v);
		}
	}
	
}

int LCA(int u, int v){
    if(level[v] > level[u]) swap(u, v);

    for(int i = MAXL - 1; i>=0; i--)
        if(level[u] - (1<<i) >= level[v]) u = ans[u][i];

    if(u == v) return u;

    for(int i = MAXL - 1; i>=0; i--)
    if(ans[u][i] != -1 & ans[u][i] != ans[v][i])
    {
       u = ans[u][i];
       v = ans[v][i];
    }

    return ans[u][0];
}

int dist(int a,int b){
	return level[a] + level[b] - 2*level[LCA(a,b)];
}

struct query{
 int a,b,d,id;
 query(){}
 query(int _a,int _b,int _d,int i){
 	a = _a;
 	b = _b;
 	d = _d;
 	id = i;
 }
};

int cmp(query a,query b){
	return a.d > b.d;
}
int mark[MAXN];
int markf[MAXN];
int instack[MAXN];

void go(int a,int b){
	int lca = LCA(a,b);
	set<int> S1,S2;
	vector<int> v1,v2;
	while(a!=lca){
		if(mark[a]){
			cout<<"No"<<endl;
			exit(0);
		}
		mark[a] = 1;
		v1.pb(a);
		a = pai[a];
	}

	if(mark[lca]){
		cout<<"No"<<endl;
		exit(0);
	}
	mark[lca] = 1;

	v1.pb(lca);
	while(b!=lca){
		if(mark[b]){
			cout<<"No"<<endl;
			exit(0);
		}
		mark[b] = 1;
		v2.pb(b);
		b = pai[b];
	}

	for(int i=(int)v2.size() - 1;i>=0;i--){
		v1.pb(v2[i]);	
	}
	
	stack<set<int> > st;
	for(int it=0;it<v1.size();it++){
		int x = v1[it];


		set<int> col,fec;
		for(int i=0;i<ini[x].size();i++){
			S1.insert(ini[x][i]);
			if(!instack[ini[x][i]])col.insert(ini[x][i]);
			else fec.insert(ini[x][i]);
			instack[ini[x][i]] = 1;
		}
		for(int i=0;i<fim[x].size();i++){
			S2.insert(fim[x][i]);
			
			if(!instack[fim[x][i]])col.insert(fim[x][i]);
			else fec.insert(fim[x][i]);
			instack[fim[x][i]] = 1;

		}
		if(fec.size() && col.size()){
			cout<<"No"<<endl;
			exit(0);
		}
		// sweep:
		while(fec.size()){
			if(st.empty()){
				cout<<"No"<<endl;
				exit(0);
			}
			set<int> S = st.top();
			st.pop();

			if(S.size() > fec.size()){
				
				for(set<int>::iterator it = fec.begin();it!=fec.end();it++){
					if(S.find(*it)!=S.end()){
						S.erase(*it);
					}else{
						cout<<"No"<<endl;
						exit(0);
					}
				}
				if(S.size()){
					st.push(S);
				}
				fec.clear();
			}else{

				for(set<int>::iterator it = S.begin();it!=S.end();it++){
					if(fec.find(*it)!=fec.end()){
						fec.erase(*it);
					}else{
						cout<<"No"<<endl;
						exit(0);
					}
				}
				S.clear();
			}

		}

		if(col.size())st.push(col);
	}

	if(S1!=S2){
		cout<<"No"<<endl;
		exit(0);
	}
	
	for(set<int>::iterator it = S1.begin();it!=S1.end();it++){
		if(markf[*it]){
			cout<<"No"<<endl;
			exit(0);
		}
		markf[*it] = 1;
	}

}	

int main(){
	int n,f;
	cin>>n>>f;
	for(int i=0;i<n-1;i++){
		int a,b;
		cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	memset(ans, -1, sizeof ans);
	pai[1] = 1;
	dfs(1,-1);
	for(int i=1;i<=n;i++){
		ans[i][0] = pai[i];
	}
	for(int j=1;j<MAXL;j++){
		for(int i=1;i<=n;i++){
			ans[i][j] = ans[ans[i][j-1]][j-1];
		}
	}
	vector<query> qry;
	for(int i=0;i<f;i++){
		int a,b;
		cin>>a>>b;
		if(a==b)continue;
		ini[a].pb(i);
		fim[b].pb(i);

		qry.pb(query(a,b,dist(a,b),i));
	}

	sort(qry.begin(),qry.end(),cmp);
	for(int i=0;i< (int) qry.size();i++){
		int a = qry[i].a;
		int b = qry[i].b;
		int id = qry[i].id;
		if(markf[id])continue;
		go(a,b);
	}
	
	cout<<"Yes"<<endl;
}