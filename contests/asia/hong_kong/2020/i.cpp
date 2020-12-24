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
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
const int N = 300005;
int n , m;
set<pair<int, int > > want[N];
int lazy2[N][3];
vi q[N];
int Y[N];
int lazy[N];
int H[N];
void add(int x){	
	int ha = Y[x] / sz(q[x]) + (Y[x]%sz(q[x]) ? 1 : 0);
	H[x] = ha;
	int ff = 0;
	for(auto w : q[x]){
		lazy2[x][ff++] = lazy[w];
		want[w].insert({ha + lazy[w],x});
	}
}

void erase(int x){
	int ff = 0;
	for(auto w : q[x]){
		auto u = *want[w].lower_bound({H[x] + lazy2[x][ff++] , x});
		Y[x] -= lazy[w] - lazy2[x][ff-1];
		Y[x] = max(Y[x] , 0);
		want[w].erase(u);
	}
}

int32_t main(){
	scanf("%d%d" , &n , &m);
	int pid = 0;
	int last = 0;
	for(int i = 0 ; i < m ; i ++){
		int t;
		scanf("%d" , &t);
		if(t == 1){
			++pid;
			int k;
			scanf("%d%d" , &Y[pid] , &k);
			Y[pid] ^= last;
			q[pid] = vi(k);
			rep(j,0,k){
				scanf("%d" , &q[pid][j]);
				q[pid][j] ^= last;
			}
			add(pid);
		}
		else{
			int x , y;
			vi cabo;
			scanf("%d%d" , &x , &y);
			x ^= last, y^= last;
			lazy[x] += y;
			while(sz(want[x]) && ((begin(want[x]))->first) <= lazy[x]){
				auto u = *begin(want[x]);
				erase(u.second);
				if(Y[u.second] == 0){
					cabo.push_back(u.second);
				}
				else{
					add(u.second);
				}
			}
			last = sz(cabo);
			sort(all(cabo));
			if(sz(cabo) == 0)
				printf("0\n");
			else{
			printf("%d " , sz(cabo));
			rep(j,0,sz(cabo)){
				auto w = cabo[j];
				if(j == (sz(cabo) - 1))
					printf("%d\n" , w);
				else
					printf("%d " , w);
				
				

			}
		}
	}
}
}
