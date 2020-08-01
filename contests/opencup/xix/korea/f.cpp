#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define fastio ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
#define int long long
typedef long long ll;

typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

map<ll,ll> mp;
ll cur=0;

const int N = 1010;
pii no[N];

void go(ll n){
	if(mp.count(n))return;
	if(n == 1){
		no[cur] = pii(-1,-1);
		mp[n] = cur ++ ;
		return;
	}
	if(n%2==0){
		go(n/2);
		no[cur] = pii(mp[n/2],mp[n/2]);
		
	}
	else{	
		go(n/2);go((n+1)/2);
		no[cur] = pii(mp[(n+1)/2],mp[(n)/2]);
	}
		mp[n]=cur++;
}

void solve(){
	ll n;
	cin>>n;
	cur=0;
	mp.clear();
	go(n);

	assert(cur<=125);
	cout << cur << endl;
	for(int i=0;i<cur;i++){
		cout << no[i].ff<<" "<<no[i].ss<<endl;
	}
	cout << cur - 1 << endl;
}

int32_t main(){
   int T;
   cin>>T;
   while(T--){
	  solve();
   }
}