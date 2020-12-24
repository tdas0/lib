#include <algorithm>
#include <iostream>
#include <assert.h>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <bitset>
#include <string.h>
using namespace std;
#define F first
#define S second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define all(x) (x).begin, (x).end
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
string s;
vs pat;



int32_t main(){
	pat.push_back("");
	for(int j = 1 ; j <= 16 ; j ++){
		string u = pat.back();
		string v = u;
		reverse(v.begin() , v.end());
		for(auto & w : v) w = (w == 'L' ? 'R' : 'L');
		string opt = u;
		opt.push_back('L');
		for(auto w : v)	 opt.push_back(w);
		pat.push_back(opt);
	}
	int t;
	cin >> t;
	int z = 0;
	while(t--){
		int x ;
		cin >> x >> s;
		bool ok = false;
		for(int j = 1 ; j < min(x+1, sz(pat)) ; j ++){
			for(int l = 0 ; l < sz(pat[j]) - sz(s) + 1; l++){
				if(pat[j].substr(l , sz(s)) == s){
					ok = true;
					break;
				}
			}
			if(ok) break;
		}
		cout << "Case " << ++z <<": ";
		cout << (ok ? "Yes" :"No") << endl;
	}
}