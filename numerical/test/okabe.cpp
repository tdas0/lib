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
	friend Mat pow(Mat a, ll p){
		Mat res(a.n,a.m); rep(i,0,a.n) res.d[i][i] = 1;
		for(; p ; p/=2 , a *= a) if(p&1) res *= a;
		return res;
	}
 };

// end of Matrix


int32_t main(){
	// test
	ModularRing<32> a = 33;
	cout << a <<" "<< a*32 << endl; ;
}	