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

string s[7];

int f(vs cur){
	string empty = "....";
	if(cur[3] == empty){ // 0 , 1 , 7
		if(cur[0] == empty)
			return 1;
		else if(cur[6] == empty)
			return 7;
		else 
			return 0;
	}
	else{ // 2, 3, 4, 5, 6, 8, 9
		string p1, p2, p3, p4;
		for(int i = 0 ; i <= 3 ; i ++)
			p1.push_back(cur[i][0]) , p3.push_back(cur[i][3]);
		for(int i = 3 ; i <= 6 ; i ++)
			p2.push_back(cur[i][0]) , p4.push_back(cur[i][3]);
		if(p1 == empty && p4 == empty)
			return 2;
		if(p1 == empty && p2 == empty)
			return 3;
		if(p2 == empty && cur[0] == empty && cur[6] == empty)
			return 4;
		if(p2 == empty && p3 == empty)
			return 5;
		if(p3 == empty)
			return 6;
		if(p2 == empty)
			return 9;
		return 8;
	}

}

int32_t main(){
	int t;
	cin >> t;
	while(t--){
		for(int i = 0 ; i < 7; i ++){
			cin >> s[i];
		}
		vector<vs> parse;
		vs curr;
		for(int i = 0 ; i < 7 ; i ++){
			curr.push_back(s[i].substr(0,4));
		}
		parse.push_back(curr);
		curr.clear();
		for(int i = 0 ; i < 7 ; i ++){
			curr.push_back(s[i].substr(5,4));
		}
		parse.push_back(curr);
		curr.clear();
		for(int i = 0 ; i < 7 ; i ++){
			curr.push_back(s[i].substr(12,4));
		}
		parse.push_back(curr);
		curr.clear();
		for(int i = 0 ; i < 7 ; i ++){
			curr.push_back(s[i].substr(17,4));
		}
		parse.push_back(curr);
		curr.clear();
		int cnt = 0;
		for(auto w : parse){
			cnt ++ ;
			cout << f(w);
			if(cnt == 2){
				cout <<":";
			}
		}
		cout<<endl;
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
