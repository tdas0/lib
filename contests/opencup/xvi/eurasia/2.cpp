#include <bits/stdc++.h>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define sz(x) (int)(x).size()
#define pb push_back

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef pair<ll,ll> pll;
typedef vector<string> vs;
typedef vector<pll> vpl;
typedef vector<int> vi;

ll modpow(ll b, ll e ,ll mod){
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
string wl;
map<int, pii> range;
vs v ;
int in = 0 , ptr = 0 , n;
int id[1<<19];
int build(int l , int r , int curr = 1){
	int currin = in ++, mid = l + (r-l)/2;
	if(l == r){
		range[l] = pii(currin, in);
		return l;
	}
	else{
		int a = build(l ,mid , 2*curr);
		int b = build(mid+1, r , 2*curr+1);
		if(wl[id[curr]] == 'W'){
			range[a] = pii(currin , in);
			return a;
		}
		else range[b] = pii(currin ,in);
		return b;
	}
}




bool inx(pii a , pii b){
	return a.first <= b.first && b.second <= a.second;
}

map<string, int> ord;

int32_t main(){
	cin >> n;
	v = vs(1<<n);
	rep(i,0,1<<n) cin >> v[i] , ord[v[i]] = i;
	cin >> wl;
	int fz = sz(wl);
	int atual = 1;
	int ssz = 1;
	for(int i = 0 ; i < n ;i ++){
		for(int j = ssz - 1 ; j >= 0 ; j --){
			id[atual + j] = --fz;
		}
		atual += ssz;
		ssz *= 2;
	}
	build(0, (1<<n) - 1);
	int Q;
	cin >> Q;
	while(Q--){
		string a, b;
		cin >> a >> b;
		if(inx(range[ord[a]] , range[ord[b]])) cout <<"Win" << endl;
		else if(inx(range[ord[b]] , range[ord[a]])) cout <<"Lose" << endl;
		else cout << "Unknown" << endl;
	}
}

/* clever stuff:
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and STAY ORGANIZED
	* Keep it simple stupid
	* WRITE STUFF DOWN
	* math -> gcd / lcm / divisors? 
*/
