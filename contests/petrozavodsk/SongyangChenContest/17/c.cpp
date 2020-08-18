#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define int long long
#define endl '\n'
#define pb push_back
const int N = 1e6 + 10;
int mark[N],mark2[N];
ll ans[N];
const int M = 998244353;
ll k;

vector<ll> pr;

void crivo(){
	for(int i=2;i<N;i++){
		
		if(!mark[i]){
			pr.pb(i);
			for(int j=2*i;j<N;j+=i){
				mark[j]=1;
			}
		}
	}
}

void crivo_segmentado(ll l,ll r){
	

	for(ll i = l;i<=r;i++){
		mark2[i-l] = i;
		ans[i-l] = 1;
	}

	for(int it =0;it < pr.size();it ++ ){
		ll p = pr[it];
		for(ll i = (l + p -1)/p * p ;i<=r;i+=p){
			ll cnt =0;
			while(mark2[i-l]%p==0){
				mark2[i-l]/=p;
				cnt++;
			}
			ans[i-l] = ans[i-l]*((cnt*k) + 1)%M;
		}
	}


	ll res = 0;
	for(ll i = l ;i<=r;i++){
		if(mark2[i-l]!=1){
			ll primo = mark2[i-l];
			ll cnt=0;
			while(mark2[i-l]%primo==0){
				mark2[i-l]/=primo;
				cnt++;
			}
			ans[i-l] = ans[i-l]*((cnt*k) + 1)%M;
		}
		res = (res + ans[i-l])%M;
	}

	cout << res << endl;
}

int32_t main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	crivo();
	int t;
	cin >> t;
	while(t--){
		ll l ,r;
		cin >> l >> r >> k;
		crivo_segmentado(l,r);
	}

}
