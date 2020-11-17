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

int fa[10][10];

int32_t main(){
	bool ok = true;
	int n;
	cin >> n;
	for(int i = 0 ; i < n; i ++){
		int d , l , r, c;
		cin >> d >> l >> r >> c;
		r-- , c--;
		for(int j = 0 ; j < l ; j ++){
			if(r < 0 || r >= 10 || c < 0 || c >= 10){
				ok = false;
				break;
			}
			fa[r][c]++;
			if(fa[r][c] > 1){
				ok = false; 
			}
			if(d){
				r++;
			}
			else{
				c++;
			}
		}
	}
	cout << (ok ? "Y" : "N") << endl;
}
