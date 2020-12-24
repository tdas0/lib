/**
 * Author: Tiago Domingos
 * Description: Arithmetic  Field
 * Status:tested
 */
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