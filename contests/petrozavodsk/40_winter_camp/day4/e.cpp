#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<int> vi;


const int N = 105;
int x[N],y[N];
bitset<N> Mask[(1<<20)];
vi g[N];
int pai[N],H[N];
void dfs(int v,int p = -1){
	for(int id : g[v]){
		int to = x[id] + y[id] - v;
		if(to==p)continue;
		H[to] = H[v] + 1;
		pai[to] = id;
		dfs(to,v);
	}
}
const int M = 998'244'353;

ll dp[(1<<20)];
ll C[N][N];
ll fat[N];

int n,m;

/*
ll solve(int msk){
	ll&x = dp[msk];
	if(x!=-1)return x;
	if(msk == (1<<n)-1)return x=1;
	x=0;
	int antes = Mask[msk].count();
	for(int j=0;j<n;j++){
		if(msk&(1<<j))continue;
		int novo = (Mask[msk|(1<<j)]^(Mask[msk])).count();
		int saiu = m - 1 - antes - 
	}
}*/

int main(){
	cin >> n >> m;
	fat[0] = 1;
	rep(i,1,N)fat[i] = 1ll*fat[i-1]*i%M;

	rep(i,0,N){ // C[n][k]
		C[i][0] = C[i][i] = 1;
		for(int j=1;j<i;j++){
			C[i][j] = (C[i-1][j-1] + C[i-1][j])%M;
		}
	}

	rep(i,0,m){
		cin >> x[i] >> y[i];
		if(i<=n-2){
			g[x[i]].pb(i);
			g[y[i]].pb(i);
		}
	}
	pai[1] = -1;
	dfs(1);

	rep(i,n-1,m){
		int a = x[i],b = y[i];
		int msk=0;
		while(a!=b){
			if(H[a] < H[b])swap(a,b);
			int id = pai[a];
			msk|=(1<<id);
			a = x[id] + y[id] - a;
		}
		Mask[msk][i] = 1;
		//cout << i<<" "<<msk<<endl;
	}
	n--;
	for(int i=0;i<(1<<n);i++){
		for(int j=0;j<n;j++){
			if(((1<<j)&i))continue;
			Mask[(1<<j)|i] |= Mask[i];
		}


	}


	for(int msk = (1<<n)-1;msk >= 0;msk--){

		if(msk == (1<<n)-1){
			dp[msk] = 1;
			continue;
		}

		int antes = Mask[msk].count();
		int ids = __builtin_popcount(msk);
		for(int j=0;j<n;j++){
			if(msk&(1<<j))continue;
			// boto o J:
			int agora = Mask[msk|(1<<j)].count();
			ll val = 1ll * C[m - (antes + ids + 1)][agora - antes] * fat[agora - antes]%M;

			dp[msk] = (dp[msk] + val * (ll)dp[msk|(1<<j)]%M)%M;

			//cout << msk<<" "<<j<<" += "<<dp[msk|(1<<j)]<<" * "<<C[m - (antes + ids + 1)][agora - antes] << " - C("<<m - (antes + ids + 1)<<","<<agora-antes<<")\n";
			//cout <<"agora : "<<agora<<" antes:" <<antes<<endl;
		}

	}
	int qtd = Mask[0].count();
	//cout << m<<" "<<qtd << " "<< dp[0]<<" "<<C[m][qtd] << endl;
	ll val = C[m][qtd] * fat[qtd]%M;

	dp[0] = (1ll * dp[0] * val)%M;

	cout << dp[0] << endl;


}
