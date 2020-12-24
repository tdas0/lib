#include <bits/stdc++.h>
// #define int long long
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
int t;

ll inv[30];
ll pot10[30];
int size(ll x){
	ll r = 0;
	while(x > 0){
		r ++ ;
		x /= 10;
	}
	return r;
}

vi ff(ll x){
	vi p;
	while(x>0){
		p.push_back(x%10);
		x/=10;
	}
	reverse(all(p));
	return p;
}

ll conta(vi p){
	ll r = 0;
	for(int i = 0 ; i < sz(p) ; i ++){
		for(int k = 0 ; k < i ; k  ++){
			if(p[i] > p[k]) r ++ ;
		}
	}
	return r;
}

map<ll, ll> mapa;
ll solve(ll a){
	if(size(a) <= 1) return 0;
	if(mapa.find(a) != mapa.end()) return mapa[a];
	vi p = ff(a);
	ll ans = conta(p);
	for(int i = 0 ; i < sz(p)  ; i ++){
		for(int k = (i == 0 ? 1 : 0) ; k < p[i] ; k ++){
			// printf("oi %d %d\n ", i, k);
			vi r;
			ll x = sz(p) - (i+1);
			for(int j = 0 ; j < i ; j ++){ 
				r.push_back(p[j]);
				if(x>0)
				ans += (9-p[j])*x* pot10[x-1];
			}
			r.push_back(k);
			ans +=  (9-k)*x*pot10[x-1];
			// printf(" ans = %lld\n", ans);
			ans +=  conta(r)*pot10[x];
			ans +=  inv[x];
		}
	}
	return mapa[a] = ans + solve(pot10[size(a)-1] - 1);
}

int32_t main(){
	pot10[0] = 1;
	inv[0] = 0;
	inv[1] = 0;
	for(int i = 1 ; i < 16 ; i ++){
		pot10[i] = 10 * pot10[i-1];
	}	
	for(int i = 2 ; i < 16; i ++){ // numeros de [0 ,10^i - 1] quantidade de inversões (com exatamente i digitos)
		for(int j = 0 ; j < i ; j ++){ // bruta a posição
			// agora inversões prefixo com sufixo
			// bruta o digito que vai ta aqui
			ll ru = 0;
			for(int k = 0 ; k < 10 ; k ++){
				if(i - j - 2 >= 0)
				ru += (9-k) * (i-j-1) * pot10[i-j-2];
			}
			inv[i] += ru * pot10[j];
		}
	}
	scanf("%d" , &t);
	int ij=0;
	while(t--){
		ll x , y;
		scanf("%lld%lld" , &x , &y);
		++ij;
		printf("Case %d: %lld\n", ij, solve(y)-solve(x-1));
	}
}
