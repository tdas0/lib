#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;
#define pb push_back


int32_t main(){
	fastio;
	int q;
	cin>>q;
	while(q--){
		int n;
		cin>>n;
		multiset<ll> S;
		for(int i=0;i<(1<<n) - 1;i++){
			ll x;
			cin>>x;
			S.insert(x);
		}
		vector<ll> v;
		
			bool ok = 1;
		while(sz(v) < n){
			if(S.empty()){
				ok = 0;
				break;
			}

			ll x = *S.begin();
			S.erase(S.find(x));
			v.pb(x);
			int t = sz(v) - 1;
			for(int i=1;i<(1<<t);i++){
				ll sum = x;
				for(int j=0;j<t;j++){
					if(i&(1<<j))sum+=v[j];
				}
				if(S.find(sum) == S.end()){
					ok = 0;
					break;
				}

				S.erase(S.find(sum));
			}
			if(!ok)break;

		}
		if(sz(S)!=0 or sz(v)!=n){
			ok = 0;
		}
		sort(all(v));
		if(!ok){
			cout<<"NO"<<endl;
			continue;
		}

		for(int x : v){
			cout << x<<" ";
		}
		cout << endl;

	}
}
