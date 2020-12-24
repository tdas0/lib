#include <bits/stdc++.h>
using namespace std;
#define int long long
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
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
const int N = 1000005;
ll qt[N] , t[N];


int32_t main(){
	ios::sync_with_stdio(false); cin.tie(0);
	int n;
	cin>>n;
	vi c(n);
	int pa = 0;
	ll sj = 0;
	rep(i,0,n){
		cin>>c[i];
		sj += c[i];
		if(c[i])
			pa = i;
	}
	int ans = 0;
	int l = 0, r = (int) 2e5;
	while(l<=r){
		int mid = l + (r-l)/2;
		memset(t,0, sizeof t);
		memset(qt,0,sizeof qt);
		rep(i,0,mid){
			t[i] = (i < n ? c[i] : 0) , qt[i] = 0;
		}
		int u = c[0];
		rep(i,mid,n){
			u += c[i];
		}
		t[mid]=0;
		ll zr = 1;
		
		int ok = 0, can = 0;
		int lazy=1, resp = u;
		// const int mod1 = (1000000007);
		// const int mod2 = (1000000009)
		// int hash1 = 0, hash2 = 0;
		// int h1=0,h2=0;
		for(int i = mid-1; i >= 1; i--){
			int dx = lazy-t[i];
			if(lazy > (ll)(1e17)) break;
			if(lazy > t[i]){
				lazy += dx;
				// h1
			}
			else{
				u -= dx;
			}

		}
		if(u >= lazy){
			l = mid + 1;
			ans = mid;
		}
		else{
			r = mid - 1;
		}
	}
	if(sj == 1)
		ans = max(ans , pa);
	
	cout<<ans<<"\n";
}
