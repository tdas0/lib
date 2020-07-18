#include <bits/stdc++.h>
using namespace std;
#define allin(a , x) for(auto a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<int> vi;
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
typedef array<int , 6> arr;
vi cycle;
int g[2900005][6];
bool vis[2900005][6];
arr curr;
int oposto[6];
int nimber(int x , int y){
	if(x<= 0) return 0;
	if(vis[x][y]) return g[x][y];
	vis[x][y] = true;
	bitset<505> mex;
	mex.set();
	for(int i = 0 ; i <= 5 ; i ++){
		if(i == y || i == oposto[y]) continue ;
		mex[nimber(x - curr[i] , i)] = 0 ;
	}
	return g[x][y] = mex._Find_first();
}

vi solve(arr p){
	curr = p;
	for(int i = 0 ; i < 2900005 ; i ++){
		for(int j =0 ; j< 6; j ++){
			vis[i][j] = false;
		}
	}	
	vi ans;
	for(int i = 0 ; i < 2900005 ; i ++){
		ans.push_back(nimber(i,0)); 
	}
	return ans;
}

int32_t main(){
	oposto[0] = 5 , oposto[1] = 4, oposto[2] = 3 , oposto[3] = 2, oposto[4] = 1 , oposto[5] = 0 ;
	arr atual;
	cin >> atual[0] >> atual[1] >> atual[2] >> atual[3] >> atual[4] >> atual[5];
	ll S; int q;
	cin >> S >> q; q--;
	bitset<6> jf;
	arr z;
	int x = 1;
	z[0] = atual[q] , z[5] = atual[oposto[q]];
	jf[q] = 1 , jf[oposto[q]] = 1;
	while(x != 3){
		for(int i = 0 ; i < 6 ; i ++){
			if(!jf[i]){
				z[x] = atual[i];
				z[6 - x - 1] = atual[oposto[i]];
				jf[i] = 1 , jf[oposto[i]] = 1;
				break ;
			}
		}
		x ++ ;
	}
	cycle = solve(z);
	S -= z[0];
	if(S < 0){
		cout << "BOB" << endl;
	}
	else if(S < 2900005){
		cout << (cycle[S] ? "ADA" : "BOB") << endl;
	}
	else{
		vi curr;
		for(int i = 40005 ; i <2900005; i++){
			curr.push_back(cycle[i]);
		}
		cout << (curr[(S - 40005) % sz(curr)] ? "ADA" :"BOB") << endl;
	}
}