#include <bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;


const int N = 210;
const double inf = 1e10;

double d[N];
int pai[N];
double f[N],x[N],y[N];
double sq(double x){
	return x*x;
}
double dist(int a,int b){
	return sqrt(sq(f[a]-f[b])*25 + sq(x[a] - x[b]) + sq(y[a] - y[b]));
}
typedef pair<int,double> pid;
typedef pair<double,int> pdi;

vector<pid> g[N];

int vis[N];
int n;
void DJ(int s,int t){
	priority_queue<pdi,vector<pdi>,greater<pdi> >pq;
	for(int i=0;i<n;i++){
		d[i] = inf;
		vis[i] = 0;
		pai[i] = -1;
	}
	d[s] = 0;
	pq.push(pdi(0,s));

	while(!pq.empty()){
		int cur = pq.top().ss;
		pq.pop();
		if(vis[cur])continue;
		vis[cur] = 1;
		for(auto to : g[cur]){
			if(d[to.ff] > d[cur] + to.ss){
				d[to.ff] = d[cur] + to.ss;
				pai[to.ff] = cur;
				pq.push(pdi(d[to.ff],to.ff));
			}
		}
	}

	
	int cur = t;
	vector<int> ans;

	while(cur!=s){
		ans.pb(cur);
		cur = pai[cur];
	}
	ans.pb(s);
	reverse(ans.begin(),ans.end());
	for(int x : ans){
		cout << x<<" ";
	}
	cout << endl;

}


int main(){
  int m;
  cin>>n>>m;
  for(int i=0;i<n;i++){
  	cin >> f[i] >> x[i] >> y[i];
  }
  
  for(int i=0;i<m;i++){
  	int a,b;
  	string s;
  	cin>>a>>b>>s;
  	if(s=="walking" or s=="stairs"){
  		g[a].pb(pid(b,dist(a,b)));
  		g[b].pb(pid(a,dist(a,b)));
  	}else if(s=="lift"){
  		g[a].pb(pid(b,1.0));
  		g[b].pb(pid(a,1.0));
  	}else{
  		g[a].pb(pid(b,1.0));
  		g[b].pb(pid(a,dist(a,b)*3.0));
  	}


  }

  int q;
  cin>>q;
  while(q--){
  	int a,b;
  	cin>>a>>b;
  	DJ(a,b);
  }


}