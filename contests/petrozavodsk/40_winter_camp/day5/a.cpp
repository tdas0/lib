#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
#define ff first
#define ss second
#define all(x) x.begin(),x.end()
using namespace std;
typedef pair<int,int> pii;
#define endl '\n'
typedef long long ll;
typedef vector<int> vi;

int v[11][1010];
int ok[1010];
int out[1010];
int sla[11];

	int n,m;
void go(int msk){
	for(int j=0;j<m;j++){
		if(!(msk&(1<<j))){
			int pt = 0;
			while(out[v[j][pt]])pt++;
			out[v[j][pt]]=1;
			ok[v[j][pt]]=1;
			go(msk|(1<<j));
			out[v[j][pt]]=0;
		}
	}
}

int32_t main(){
	scanf("%d%d",&n,&m);
	vi p;
	rep(i,0,m)p.pb(i);
	rep(i,0,m){
		rep(j,0,n)scanf("%d",&v[i][j]),v[i][j]--;
	}

	go(0);

	
	vi res;
	rep(i,0,n){
		if(ok[i])res.pb(i+1);
	}
	cout << res.size() << endl;
	for(auto it : res)cout<<it<<" ";
	cout<<endl;
}
