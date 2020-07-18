#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin() , (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
int N , A, R, T;
map<pii ,int> cnt;
map<int,pii> rcnt;
int cc = 0;
struct trip{
	int t;
	vector<int> v;
	vector<int> coef;
};
vector<trip> X;
// begin
int mod = 13;
int modinv(int x){
	return modpow(((x%13) + 13)%13 , 13-2,13)%13;
}
int solveLinear(vector<vi>& A, vi& b, vi& x) {
	int n = sz(A), m = sz(x), rank = 0, br, bc;
	vi col(m); 
	for(int i = 0 ; i < sz(col) ; i++) col[i] = i;
	rep(i,0,n) {
		int v, bv = -1;
		rep(r,i,n) rep(c,i,m)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		rep(j,i,n) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		rep(j,0,n) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		rep(j,i+1,n) {
			int fac = (A[j][i] * bv) % mod;
			b[j] = ((b[j] - fac * b[i]) % mod + mod)%mod;
			rep(k,i+1,m) A[j][k] = ((A[j][k] - fac*A[i][k]) % mod + mod)%mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (int i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		rep(j,0,i)
			b[j] = ((b[j] - A[j][i] * b[i])%mod + mod)%mod;
	}
	return rank;
}
// end of system of equations solver
int dist[1000][1000];

int32_t main(){
	cin >> N >> A >> R >> T;
	X = vector<trip>(T);
	vi b;
	vector<vi> a;
	for(int i = 0 ; i < T; i ++){
		cin >> X[i].t;
		b.push_back(X[i].t);
		int d;
		cin >> d;
		X[i].v = vector<int>(d);
		for(int j = 0 ; j < d ; j ++ ){
			cin >> X[i].v[j];
		}
		for(int j = 0 ; j < d-1 ; j ++){
			pair<int,int> u = pair<int,int> (X[i].v[j] , X[i].v[j+1]);
			if(u.first > u.second) swap(u.first, u.second);
			if(!cnt.count(u)){
				cnt[u] = cc++;
				rcnt[cnt[u]] = u;
			}
		}
	}
	for(int i = 0 ; i < T; i ++){
		vi pp(cc);
		int d = sz(X[i].v);
		for(int j = 0 ; j< d-1 ; j ++){
			pair<int,int> u = pair<int,int>(X[i].v[j] , X[i].v[j+1]);
			if(u.first > u.second) swap(u.first,u.second);
			pp[cnt[u]]++;
		}
		rep(j,0,sz(pp)){
			pp[j] %= mod;
		}
		a.push_back(pp);
	}
	rep(i,0,N+1){
		rep(j,0,N+1) dist[i][j] = (int) 1e9;
	}
	vi x(cc);	
	solveLinear(a , b, x);
	rep(i,0,sz(x)){
		x[i] = ((x[i] + mod)%mod + mod)%mod;
		pair<int,int> u = rcnt[i];
		dist[u.first][u.second] = (x[i]+13)%13;
		dist[u.second][u.first] = (x[i]+13)%13;
	}
	rep(i,0,N+1) dist[i][i] = 0;
	rep(k,0,N+1) rep(i,0,N+1) rep(j,0,N+1){
		dist[i][j] = min(dist[i][j] , dist[i][k] + dist[k][j]);
	}
	cout << dist[A][R] << endl;
}

