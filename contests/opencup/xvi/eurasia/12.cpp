#include <bits/stdc++.h>
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

map<char ,int> lco , wco;
map<int,int> lp;
int ans[5];
bool vis[25][25];
int n, m;
string field[15] = {"rwwgwwwrwwwgwwr","wbwwwywwwywwwbw","wwbwwwgwgwwwbww","gwwbwwwgwwwbwwg","wwwwbwwwwwbwwww","wywwwwwwwwwwwyw","wwgwwwgwgwwwgww","rwwgwwwswwwgwwr","wwgwwwgwgwwwgww","wywwwwwwwwwwwyw","wwwwbwwwwwbwwww","gwwbwwwgwwwbwwg","wwbwwwgwgwwwbww","wbwwwywwwywwwbw","rwwgwwwrwwwgwwr"};

int32_t main(){
	lco['w'] = 1;
	lco['s'] = 1;
	lco['g'] = 2;
	lco['y'] = 3;
	lco['b'] = 1;
	lco['r'] = 1;
	wco['w'] = 1;
	wco['s'] = 1;
	wco['g'] = 1;
	wco['y'] = 1;
	wco['b'] = 2;
	wco['r'] = 3;
	lp[2]=     3;
	lp[1]=     1;
	lp[3]=     2;
	lp[4]=     3;
	lp[5]=     2;
	lp[6]=     1;
	lp[7]=     5;
	lp[8]=     5;
	lp[9]=     1;
	lp[10]=     2;
	lp[11]=     2;
	lp[12]=     2;
	lp[13]=     2;
	lp[14]=     1;
	lp[15]=     1;
	lp[16]=     2;
	lp[17]=     2;
	lp[18]=     2;
	lp[19]=     2;
	lp[20]=     3;
	lp[21]=    10;
	lp[22]=     5;
	lp[23]=   10;
	lp[24]=     5;
	lp[25]=    10;
	lp[26]=    10;
	lp[27]=    10;
	lp[28]=     5;
	lp[29]=     5;
	lp[30]=    10;
	lp[31]=    10;
	lp[32]=     3;
	cin >> n >> m;
	rep(iff,0,m){
		int rf = 0;
		cin >> rf;
		int tot = 0;
		int coc = 0;
		while(rf--){
			int w; 
			cin >> w;
			int sum = 0;
			int lzf = 1;
			char p;
			cin >> p;
			int lx , rx;
			cin >> lx >> rx;
			lx -- , rx --;
			for(int i = 0 ; i < w; i ++){
				pii cord =pii(rx + (p == 'v' ? +i : 0) , lx + (p == 'h' ? i : 0)); 
				int fz = 0;
				cin >> fz;
				if(!vis[cord.first][cord.second]){
					coc ++ ;
					vis[cord.first][cord.second] = 1;
				}
				sum += lp[fz] * lco[field[cord.first][cord.second]];
				lzf *= wco[field[cord.first][cord.second]];
			}
			tot += sum * lzf;
		}
		ans[iff%n] += tot + (coc == 7 ? 15 : 0);
	}
	rep(i,0,n){
		cout << ans[i] <<endl;
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
