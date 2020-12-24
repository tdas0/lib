#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
typedef long long ll;

int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int q, n;
	cin>>q;
	while(q--){
		cin>>n;
		map<string, ll> qtd;
		for(int i = 1; i<=n;i++){
			string a, b;
			cin>>a>>b;
			qtd[b] ++;
		}
		ll ans=1LL;
		for(auto ss: qtd){
			ans *= (ss.s + 1);
		}
		cout<<ans-1LL<<"\n";
	}
}
