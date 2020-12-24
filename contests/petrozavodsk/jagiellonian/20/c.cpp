#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <climits>

using namespace std;

#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) begin(x) , end(x)
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


int32_t main(){
	int t;
	scanf("%d" , &t);
	while(t--){
		int n ; ll d;
		scanf("%d%lld" , &n , &d);
		vl v(n);
		rep(i,0,n) scanf("%lld" , &v[i]);
		sort(all(v));
		rep(i,0,n) v[i] = v[i] - (i*1ll)* d;
		priority_queue<ll> pq;
		ll ans= 0 ;
		rep(i,0,n){
			if(v[i] < 0) ans -= v[i];
			v[i] = max(v[i] , 0ll);
		}
		pq.push(0);
		pq.push(v[0]);
		rep(i,1,n){
			pq.push(v[i]);
			if(pq.top() > v[i]){
				ans += pq.top() - v[i];
				pq.pop();
				pq.push(v[i]);
			}
		}
		cout << ans << endl;
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