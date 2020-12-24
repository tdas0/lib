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
bool isp[30];
vi primes = {2 , 3 , 5 , 7 , 11 ,13 , 17 , 19, 23};
vector<char> alfa = {'a', 'b', 'd', 'f', 'j', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'u', 'v', 'x', 'y', 'z'};
map<char,int> pos;
vector< vi > vec;
int conta(int x , int y){
	int ans = 0;
	while(x > 0){
		ans += x/y;
		x /= y;
	}
	return ans;
}
vi cur , state;
string opt;
string curr;
void upd(){
	string r;
	for(int j = 0 ; j < sz(alfa) ; j ++){
		for(int k = 0 ; k < cur[j] ; k ++) r.push_back(alfa[j]);
	}
	if(r == curr){
		next_permutation(all(r));
	}
	if(!sz(opt)){
		if(r != curr) opt = r;
	}
	else{
		if(r != curr) opt = min(opt, r);
	}
}


void gen(int idd){
	bool ok = 1;
	for(int j = 0 ; j < sz(state); j ++){
		if(state[j]) ok = 0;
	}
	if(ok){
		upd();
		return ;
	}
	if(idd < 0) return ;
	char c = alfa[idd];
	int u = c - 'a' + 2;
	int pp = pos[c] , mx = INT_MAX;
	for(int j = 0 ; j < sz(primes) ; j ++){
		if(state[j] && !vec[pp][j]){
			return ;
		}
		if(vec[pp][j])
			mx = min(mx , state[j] / vec[pp][j]);
	}
	if(mx == INT_MAX){
		mx = 0;
	} 		
	if(isp[u]){
		for(int j = 0 ; j < sz(primes) ; j ++){
			if(primes[j] == u && mx*vec[pp][j] != state[j]){
				return ; 
			}
		}
		for(int j = 0 ; j < sz(primes) ; j ++){
			state[j] -= mx * vec[pp][j];
		}
		cur[pp] += mx;				
		gen(idd -1);
		cur[pp] -= mx;
		for(int j = 0 ; j < sz(primes) ; j ++){
			state[j] += mx * vec[pp][j];
		}	
	}
	else{
		for(int j = 0 ; j <= mx ; j++){
			for(int i = 0 ; i < sz(primes) ; i ++){
				state[i] -= j * vec[pp][i];
			}
			cur[pp] += j;
			gen(idd-1);
			cur[pp] -= j;
			for(int i = 0 ; i < sz(primes) ; i ++){
				state[i] += j * vec[pp][i];
			}
		}
	}
}


int32_t main(){
	int zzz = 0;
	for(auto w : alfa){
		pos[w] = zzz++;
		int u = w - 'a' + 2;
		vi a(sz(primes) , 0);
		for(int j = 0 ;j < sz(primes); j++){
			a[j] += conta(u , primes[j]);
		}
		vec.push_back(a);
	}
	for(auto w : primes) isp[w] = 1;
	int t, z= 0;
	cin >> t;
	while(t--){
		string s;
		cin >> s;
		curr = s;
		state = vi(sz(primes) , 0);
		for(auto w : s){
			int u = w - 'a' + 2;
			for(int j = 0; j < sz(primes) ; j++) 
				state[j] += conta(u,primes[j]);			
		}
		cur = vi(sz(alfa) , 0);
		opt = "";
		gen(sz(alfa) - 1);
		if(sz(opt) == 0) opt = "Impossible";
		if(opt == s){
			next_permutation(all(opt));
		}
		if(opt == s){
			opt = "Impossible";
		}
		cout <<"Case " << ++z <<": "<< opt << endl;
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