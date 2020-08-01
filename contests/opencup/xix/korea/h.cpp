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

int gcd(int a,int b){
	return __gcd(a,b);
}

ll f(ll x,ll y){
	ll res=0;
	for(int a=1;a<=999;a++){
		for(int b=1;b+a<=999;b++){
			if(gcd(a,b)!=1)continue;
			res+=min(x/a,y/b);
		}
	}

	return res;
}

int main(){
	ll A,B,C,D;
	cin >> A >> B >> C >> D;
	ll res = f(B,D) - f(A-1,D) - f(B,C-1) + f(A-1,C-1); 
	cout << res << endl;
}