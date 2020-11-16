#include <bits/stdc++.h>
#define ld long double
#define endl "\n"
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define pb push_back
#define mp(a,b) make_pair(a,b)
#define ms(v,x) memset(v,x,sizeof(v))
#define all(v) v.begin(),v.end()
#define ff first
#define ss second
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define per(i, a, b) for(int i = b-1; i>=a ; i--)
#define trav(a, x) for(auto& a : x)
#define allin(a , x) for(auto a : x)
#define Unique(v) sort(all(v));v.erase(unique(all(v)),v.end());
#define sz(v) ((int)v.size())
//#define int long long
using namespace std;
typedef vector<int> vi;
#define y1 abacaba
#define left oooooopss
#define db(x) cerr << #x <<" == "<<x << endl;
#define db2(x,y) cerr<<#x <<" == "<<x<<", "<<#y<<" == "<<y<<endl;
#define db3(x,y,z) cerr << #x<<" == "<<x<<", "<<#y<<" == "<<y<<", "<<#z<<" == "<<z<<endl; 
#define prl cerr<<"called: "<< __LINE__ << endl;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
/*inline ll mod(ll n, ll m ){ ll ret = n%m; if(ret < 0) ret += m; return ret; }
ll gcd(ll a, ll b){return (b == 0LL ? a : gcd(b, a%b));}
ll exp(ll b, ll e ,ll m) {
  b%=m;
  ll ans = 1;
  for (; e; b = b * b % m, e /= 2)
    if (e & 1) ans = ans * b % m;
  return mod(ans,m);
}*/

ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
const int mod = 2;
int modinv(int x){
	return modpow(x , mod - 2 , mod);
}
int solveLinear(vector<vi>& A, vi& b, vi& x) {
	rep(i,0,sz(A)){
		rep(j,0,sz(A[i])){
			A[i][j] = ((A[i][j])%mod + mod)%mod;
		}
	}
	rep(i,0,sz(b)){
		b[i] = (b[i]%mod + mod)%mod;
	}
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


const int N = 150;
int deg[N];

int32_t main(){
  fastio;
  int n,m;
  cin>>n>>m;
  vector<vi>A(n,vi(n,0));
  vi b(n,1);
  vi x(n,1);
  int even = 0; 
  for(int i=0;i<m;i++){
  	int a,b;
  	cin>>a>>b;
  	a--;b--;
  	deg[a]++;
  	deg[b]++;
  	A[a][b] = A[b][a] = 1;
  }
  for(int i = 0 ; i < n; i ++){
  	if(deg[i]%2 == 0){
  		b[i] = 1;
  	}
  	else{
  		A[i][i] = 1;
  		b[i] = 0;
  	}
  }
  int odd=0;
  for(int i=0;i<n;i++){
  	if(deg[i]%2==0)even=1;
  	else odd = 1;
  }
  if(odd && !even){
  	cout<<"Y"<<endl;
  }else{
  	vi x(n,0);
  	int res = solveLinear(A,b,x);
  	
  	if(res==-1)cout<<"N"<<endl;
  	else cout<<"Y"<<endl;
  }
  
}