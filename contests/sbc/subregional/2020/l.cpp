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
int n , m;
string s[50];
int fa[50][50];
int32_t main(){
	cin >> n >> m;
	for(int i = 0 ; i < n; i ++){
		cin >> s[i];
	}
	int q;
	cin >> q;
	rep(xq,0,q){
		string c;
		cin >> c;
		map<char,int> cur;
		for(auto w : c){
			cur[w]++;
		}
		rep(i,0,n){
			rep(j,0,m){
				map<char,int> f1 , f2 , f3;
				for(int k = i ; k < n ; k ++){
					f1[s[k][j]]++;
					if(f1 == cur){
						for(int kk = i ; kk <= k ; kk++){
							fa[kk][j] |= 1<<xq;
						}
					}
				}
				for(int k = j ; k < m ; k ++){
					f2[s[i][k]]++;
					if(f2 == cur){
						for(int kk = j ; kk <= k ; kk ++){
							fa[i][kk] |= 1<<xq;
						}
					}
				}
				for(int k = 0 ; i+k < n && j+k < m ; k++){
					f3[s[i+k][j+k]]++;
					if(f3 == cur){
						for(int kk = 0 ; kk <= k ; kk++){
							fa[i+kk][j+kk] |= 1<<xq;
						}
					}
				}
				map<char,int> f4;
				for(int k = 0 ; (i-k) >= 0 && (j+k) < m ; k ++){
					f4[s[i-k][j+k]]++;
					if(f4 == cur){
						for(int kk = 0 ; kk <= k ; kk ++){
							fa[i-kk][j+kk] |= 1<<xq;
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for(int i = 0 ; i < n; i ++){
		for(int j = 0 ; j < m ; j ++){
			if(__builtin_popcount(fa[i][j]) > 1)
				ans ++;
		}
	}
	cout << ans << endl;
}