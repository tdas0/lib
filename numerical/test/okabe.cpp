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
ll modpow(ll b, ll e ,ll mod) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

// begin of ModularRing
template <ll MOD_> struct ModularRing {
private:
	ll v;
public:
	static const ll MOD = MOD_;
	ModularRing() : v(0) {}
	ModularRing(ll v_) : v(ll(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator ll () const { return v; }
	friend bool operator == (const ModularRing& a, const ModularRing& b) { return a.v == b.v; }
	friend bool operator != (const ModularRing& a, const ModularRing& b) { return a.v != b.v; }
	friend bool operator <  (const ModularRing& a, const ModularRing& b) { return a.v < b.v;  }
	friend ModularRing pow(ModularRing a ,ll p){
		ModularRing ans = 1;
		for(;p;p/=2 , a *= a) if(p&1) ans *= a;
		return ans;
	}
	ModularRing operator ~() const { // if p is prime
		return pow(*this, MOD - 2);
	}
	ModularRing& operator += (const ModularRing& o) {
		v += o.v;
		if (v >= MOD) v -= MOD;
		return *this;
	}
	ModularRing& operator -= (const ModularRing& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	ModularRing& operator *= (const ModularRing& o) {
		v = (ll)(ll(v) * ll(o.v) % MOD);
		return *this;
	}
	ModularRing& operator /= (const ModularRing& o) {
		return *this *= (~o);
	}
	friend ModularRing operator + (const ModularRing& a, const ModularRing& b) { return ModularRing(a) += b; }
	friend ModularRing operator - (const ModularRing& a, const ModularRing& b) { return ModularRing(a) -= b; }
	friend ModularRing operator * (const ModularRing& a, const ModularRing& b) { return ModularRing(a) *= b; }
	friend ModularRing operator / (const ModularRing& a, const ModularRing& b) { return ModularRing(a) /= b; }
 	friend std::ostream& operator<<(std::ostream& os, ModularRing const& a) {return os << a.v;}
};
// end 


// begin of Matrix
template<class T>
struct Mat{
	int n, m; vector< vector<T> > d;
	Mat(int n , int m): n(n) , m(m){
		d.assign(n , vector<T>(m));
	}
	Mat() : Mat(0,0) {}
	Mat(const vector<vector<T>>&_d) : n(sz(_d)) , m(sz(_d[0])) {d=_d;}
	Mat & operator+=(const Mat&a){
		rep(i,0,n) rep(j,0,m) d[i][j] += a.d[i][j];
		return *this;
	}
	Mat & operator-=(const Mat&a){
		rep(i,0,n) rep(j,0,m) d[i][j] -= a.d[i][j];
		return *this;
	}
	Mat  operator*(const Mat&a){ // m == a.n
		Mat x(n,a.m);
		rep(i,0,n) rep(j,0,m) rep(k,0,a.m)
			x.d[i][k] += d[i][j] * a.d[j][k];
		return x;
	}
	Mat operator+(const Mat&a){
		return Mat(*this)+= a;
	}
	Mat operator-(const Mat&a){
		return Mat(*this)-= a;
	}
	Mat & operator*=(const Mat&a){
		return *this = (*this)*a;
	}
	Mat & operator^=(const ll& x){
		return *this = pow(*this , x);
	}
	Mat operator^(const ll &x){
		return Mat(*this)^= x;
	}
	friend Mat pow(Mat a, ll p){
		Mat res(a.n,a.m); rep(i,0,a.n) res.d[i][i] = 1;
		for(; p ; p/=2 , a *= a) if(p&1) res *= a;
		return res;
	}
 };
// end of Matrix
int n ; ll k;
const ll mod = (ll) 1e9 + 7;
struct seg{
	ll a , b, c;
}; 
vector<seg> v;
Mat<ModularRing<mod>> f(16,16);
Mat<ModularRing<mod>> dp(1,16);

int32_t main(){
	cin >> n >> k;
	v = vector<seg>(n);
	rep(i,0,n){
		cin >> v[i].a >> v[i].b >> v[i].c;
	}
	dp.d[0][0] = 1;
	rep(i,0,16) f.d[i][i] = 1;
	rep(ix,0,n){
		ll p = min(v[ix].b , k) - v[ix].a;
		Mat<ModularRing<mod>> f2(16,16);
		rep(i,0,v[ix].c+1){
			for(int j = i - 1 ; j <= (i+1) ; j ++){
				if(j >= 0 && j <= v[ix].c){
					f2.d[j][i] = 1;
				}
			}
		}
		f2 ^= p;
		f *= f2;
	}
	dp *= f;
	ModularRing<mod> ans = 0 ;
	cout << dp.d[0][0] << endl; 
}	
