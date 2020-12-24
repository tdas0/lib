#include <bits/stdc++.h>
#define sz(x) (int)(x).size()
#define pb push_back
#define f first
#define s second
#define int long long

using namespace std;
typedef pair<int, int> pii;
#define N 30010
int n, m, k, t,v[N];
vector<pii> app[N];
long double p[N][55];
long double sum[55][N];
vector<int> rev[N];
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	ifstream cin("input.txt");
 ofstream cout("output.txt");
	cin>>n>>m>>k>>t;
	for(int i = 1; i <= n; i++){
		cin>>v[i];
	}
	vector<int> testa;
	for(int i = 1; i <= k; i++){
		int p,q,r;
		cin>>p>>q>>r;
		app[p].pb({q, r});
		rev[q].pb(p);
		if(q == m) testa.pb(r);
	}
	// for(int i = 1; i <= n; i++) sort(all(app[i]));
	for(int i = 1; i <= t; i++){
		for(int j = 1; j < m; j++){
			cin>>p[i][j];
		}
	}
	for(int i = 1; i < m; i++){
		for(int j = 1; j <= t; j++){
			sum[i][j] = sum[i][j-1] + p[j][i];
			// cout<<"sum "<<i<<", "<<j<<" = "<<sum[i][j]<<"\n";
		}
	}
	long double mx = 0;
	int id = 1;
	for(int u = 0; u < sz(testa); u++){
		int i = testa[u];
		long double ans = 0;
		for(int p = 0; p < sz(rev[m]); p++){
			int j = rev[m][p];
			int opt=0;
			long double ptot =1.0;
			for(int q = 0; q < sz(app[j]); q++){
				pii w = app[j][q];
				int coll = w.f, dia = w.s;
				if(coll == m ) opt = max(opt, dia);
				if(dia >= i or coll == m) continue;
				//alguem = 1;
				long double p_choose = sum[coll][i-1] - sum[coll][dia - 1];

				ptot *= (1.0 - p_choose);
			}
			if(opt <= i) ans += ptot * ((long double)v[j]);
		}
		if(ans > mx){
			mx = ans;
			id = i;
		}
	}
	cout<<setprecision(10)<<fixed;
	cout<<mx<<" "<<id<<"\n";
}