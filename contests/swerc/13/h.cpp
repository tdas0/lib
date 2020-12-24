#include <bits/stdc++.h>
#define f first
#define s second
#define pb push_back
#define mp make_pair
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
using namespace std;
#define int long long
typedef long long ll;
typedef pair<int, int> pii;
#define N 300050
int mod = 21092013;

int q;
vector<int>pos[2];
int dp[N], vis[N], cz;
int solve(int i){
	int ans=1;
	if(vis[i] == cz) return dp[i];
	vis[i]=cz;
	for(int j=0;j<2;j++){
		auto it=upper_bound(all(pos[j]), i);
		if(it==pos[j].end())continue;
		ans+=solve(*it);
		ans %= mod;
	}
	return dp[i]=ans;
}
int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>q;
	int caso=0;
	while(q--){
		cz++;
		pos[0].clear();
		pos[1].clear();
		caso ++;
		string s, t;
		cin>>s;
		cin>>t;
		int deep=0;
		int tot=0;
		string aux;
		for(int i=0;i<sz(s); i++){
			if(s[i] != 'U') deep++, aux.pb(s[i]);
			else if(deep>0)deep --, aux.pop_back();
			if(deep < 0) deep = 0;
		}
		reverse(all(aux));
		// cout<<"AUX "<<aux<<"\n";
		int id=0;
		for(int i=0;i<sz(t); i++){
			int id = (t[i] == 'L'?0:1);
			if(t[i] != 'U')pos[id].pb(i);
		}
		for(auto c: t) if(c != 'U') tot ++;
		int h=deep, curr=0, ans = 0;
		ans = 1 +(!pos[0].empty()?solve(pos[0][0]):0) + (!pos[1].empty()?solve(pos[1][0]) : 0);
		// cout<<"ANS "<<ans<<"\n";
		ans %= mod;
		for(int i=0;i<sz(t); i++){
			if(t[i] == 'U' and h > 0){
				h--;
				int idd = (aux[id] == 'L'?0:1);
				auto it = upper_bound(all(pos[!idd]), i);
				ans ++;
				if(it != pos[!idd].end()){
					ans += solve(*it);
				}
				ans %=mod;
				id++;
			}
			else curr ++;
		}
		ans %= mod;
		cout<<"Case "<<caso<<": "<<ans<<"\n";
	}
}
